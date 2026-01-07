# -*- coding: utf-8 -*-
from __future__ import annotations

import argparse
import os
import time
import threading
from pathlib import Path
from typing import Dict, Optional

from dotenv import load_dotenv

import src.pipelines.translate as base_translate
from src.translators.openai_trace import TraceOpenAITranslator, TraceDeepSeekTranslator


def _load_env(project_root: Optional[Path] = None) -> Dict[str, str]:
    # 어디서 실행해도 .env를 읽게 하고 싶으면 project_root를 넘기세요.
    if project_root is None:
        load_dotenv()
    else:
        load_dotenv(project_root / ".env")
    return dict(os.environ)


def _mk_run_dir(root: Path, module: str) -> Path:
    ts = time.strftime("%Y%m%d_%H%M%S")
    run_dir = root / f"trace_translate_{module}_{ts}"
    run_dir.mkdir(parents=True, exist_ok=True)
    return run_dir


def _read_text(path: Path) -> str:
    return path.read_text(encoding="utf-8")


def _resolve_prompts_dir_from_env(env: Dict[str, str]) -> Path:
    dataset = (env.get("TARGET_DATASET") or "").strip()
    if not dataset:
        raise KeyError("TARGET_DATASET is missing in env (required).")
    ds = dataset.upper()
    key = f"{ds}_PROMPTS_DIR"
    if key not in env or not str(env.get(key, "")).strip():
        raise KeyError(f"{key} is missing in env (required).")
    p = Path(env[key]).resolve()
    return p


def _resolve_base_prompt_path(env: Dict[str, str]) -> Path:
    # 원본 translate.py 기본값과 동일하게 맞춤
    p = (env.get("PROMPT_BASE_PATH") or "src/prompts/translation/base.txt").strip()
    return Path(p).resolve()


def _build_trace_translator(
    module_name: str,
    env: Dict[str, str],
    base_prompt_path: Path,
    trace_path: Path,
    lock: threading.Lock,
    full_messages: bool,
    run_tag: str,
):
    system_template = _read_text(base_prompt_path)

    if module_name == "openai":
        tr = TraceOpenAITranslator.from_env(env=env, system_template=system_template)
    elif module_name == "deepseek":
        tr = TraceDeepSeekTranslator.from_env(env=env, system_template=system_template)
    else:
        raise ValueError(f"trace_translate supports only openai/deepseek (got: {module_name})")

    tr.trace_path = trace_path
    tr.trace_lock = lock
    tr.full_messages = bool(full_messages)
    tr.run_tag = run_tag
    return tr


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--translator", choices=["openai", "deepseek"], required=True)
    ap.add_argument("--temp_root", default="./_tmp_trace")
    ap.add_argument("--full_messages", action="store_true", help="store full request messages (can be huge)")
    ap.add_argument("--no_full_messages", action="store_true", help="store summarized messages only")
    ap.add_argument("--n_variants", type=int, default=None, help="override N_VARIANTS for this run")
    ap.add_argument("--temperature", type=float, default=None, help="override TEMPERATURE for this run")
    ap.add_argument("--target_langs", default=None, help="override TARGET_LANGS (comma-separated), or leave None to use env/default")
    args = ap.parse_args()

    env = _load_env()

    # ✅ 원본과 동일한 prompts 위치 해석
    prompts_dir = _resolve_prompts_dir_from_env(env)
    base_prompt_path = _resolve_base_prompt_path(env)

    # 결과는 temp에 저장
    temp_root = Path(args.temp_root).resolve()
    run_dir = _mk_run_dir(temp_root, args.translator)
    translated_dir = run_dir / "translated"
    translated_dir.mkdir(parents=True, exist_ok=True)

    trace_path = run_dir / "_trace" / f"requests_responses_{args.translator}.jsonl"
    lock = threading.Lock()

    # overrides
    if args.n_variants is not None:
        os.environ["N_VARIANTS"] = str(args.n_variants)
        env["N_VARIANTS"] = str(args.n_variants)

    if args.temperature is not None:
        os.environ["TEMPERATURE"] = str(args.temperature)
        env["TEMPERATURE"] = str(args.temperature)

    if args.target_langs is not None:
        os.environ["TARGET_LANGS"] = args.target_langs
        env["TARGET_LANGS"] = args.target_langs

    full_messages = True
    if args.no_full_messages:
        full_messages = False
    elif args.full_messages:
        full_messages = True

    # monkey patch: translator 생성만 트레이싱 버전으로 교체
    orig_builder = getattr(base_translate, "build_translator", None)

    def _builder(module_name: str, env_: Dict[str, str], base_prompt_path_: Path):
        return _build_trace_translator(
            module_name=module_name,
            env=env_,
            base_prompt_path=base_prompt_path_,
            trace_path=trace_path,
            lock=lock,
            full_messages=full_messages,
            run_tag=f"{args.translator}",
        )

    base_translate.build_translator = _builder  # type: ignore

    dataset = (env.get("TARGET_DATASET") or "").strip()

    # target_langs 해석은 원본 translate.py가 내부에서 처리하는 부분이 있을 수 있어서,
    # 여기서는 override가 없으면 빈 리스트로 두고(=원본 로직에 맡김),
    # override가 있으면 명시 리스트로 전달합니다.
    target_langs = []
    if args.target_langs is not None:
        target_langs = [x.strip() for x in args.target_langs.split(",") if x.strip()]

    cfg = base_translate.TranslateConfig(
        dataset=dataset,
        prompts_dir=prompts_dir,
        translated_dir=translated_dir,
        modules=[args.translator],     # ✅ openai 또는 deepseek만
        target_langs=target_langs,     # override 없으면 [] (원본 처리에 맡김)
        base_prompt_path=base_prompt_path,
        temperature=float(env.get("TEMPERATURE", "0.2")),
    )

    print("[TRACE] run_dir:", run_dir)
    print("[TRACE] translated_dir:", translated_dir)
    print("[TRACE] trace_path:", trace_path)
    print("[TRACE] module:", args.translator)
    print("[TRACE] TARGET_DATASET:", dataset)
    print("[TRACE] prompts_dir:", prompts_dir, "exists=", prompts_dir.exists())
    print("[TRACE] base_prompt_path:", base_prompt_path, "exists=", base_prompt_path.exists())
    print("[TRACE] env TARGET_LANGS:", env.get("TARGET_LANGS"))
    print("[TRACE] cfg target_langs override:", cfg.target_langs)
    print("[TRACE] N_VARIANTS:", env.get("N_VARIANTS"))
    print("[TRACE] VARIANT_PARALLELISM:", env.get("VARIANT_PARALLELISM"))
    print("[TRACE] OPENAI_TIMEOUT_SEC:", env.get("OPENAI_TIMEOUT_SEC"))

    try:
        base_translate.run_translate(cfg=cfg, env=env)
    finally:
        if orig_builder is not None:
            base_translate.build_translator = orig_builder  # type: ignore

    print("[TRACE] done.")


if __name__ == "__main__":
    main()
