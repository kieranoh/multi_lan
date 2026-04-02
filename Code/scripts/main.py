#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from __future__ import annotations

import argparse
import os
import sys
from pathlib import Path
from typing import Dict, List, Optional

import warnings
import logging

os.environ["PYTHONWARNINGS"] = "ignore"
os.environ["TOKENIZERS_PARALLELISM"] = "false"
os.environ["TRANSFORMERS_VERBOSITY"] = "error"
os.environ["HF_HUB_DISABLE_SYMLINKS_WARNING"] = "1"

warnings.filterwarnings("ignore")

logging.basicConfig(level=logging.WARNING)

for name in [
    "httpx",
    "openai",
    "deepseek",
    "urllib3",
    "transformers",
]:
    logging.getLogger(name).setLevel(logging.ERROR)
    logging.getLogger(name).propagate = False

from dotenv import load_dotenv


def _ensure_importable_project_root() -> None:
    """Make repo root importable so `import src...` works when running from scripts/."""
    here = Path(__file__).resolve()
    root = here.parents[1]  # scripts/.. = repo root
    if str(root) not in sys.path:
        sys.path.insert(0, str(root))


def _set_env_if_arg(name: str, value: Optional[str]) -> None:
    if value is None:
        return
    os.environ[name] = value


def _parse_csv(v: Optional[str]) -> List[str]:
    return [x.strip().lower() for x in (v or "").split(",") if x.strip()]


def _get_translation_modules(env: Dict[str, str]) -> List[str]:
    """
    Translation modules 순서:
      deepseek -> openai -> nllb (기본)
    .env / CLI에 적힌 모듈들 중 해당되는 것만 정렬해서 반환.
    """
    mods = _parse_csv(env.get("TRANSLATION_MODULES", "openai"))
    order = { "deepseek": 1, "nllb": 0, "openai": 2}
    return sorted(mods, key=lambda m: order.get(m, 99))


def _get_generate_models(env: Dict[str, str]) -> List[str]:
    """
    Generate models 순서:
      openai -> deepseek (기본)
    .env / CLI에 적힌 모델들 중 해당되는 것만 정렬해서 반환.
    """
    mods = _parse_csv(env.get("GEN_MODELS", "openai"))
    order = {"openai": 0, "deepseek": 1}
    return sorted(mods, key=lambda m: order.get(m, 99))


def run_translate_single_module(env: Dict[str, str], *, module: str) -> None:
    """
    translate 단계: module 하나만 넣어서 순차 실행 (병행/혼합 방지)
    - stage1_forward + stage2_meta 생성
    """
    from src.pipelines.translate import (
        TranslateConfig,
        choose_target_langs,
        env_required_dataset_dirs,
        run_translate,
    )

    dataset = env["TARGET_DATASET"].strip()
    prompts_dir, translated_dir, _final_dir = env_required_dataset_dirs(env, dataset)

    target_langs = choose_target_langs(env)

    base_prompt_path = Path(env.get("PROMPT_BASE_PATH", "src/prompts/translation/base.txt")).resolve()
    if not base_prompt_path.exists():
        raise FileNotFoundError(f"base prompt template not found: {base_prompt_path}")

    temperature = float(env.get("TEMPERATURE", "0.0"))

    run_translate(
        TranslateConfig(
            dataset=dataset,
            prompts_dir=prompts_dir,
            translated_dir=translated_dir,
            modules=[module],  # ✅ 단일 모듈
            target_langs=target_langs,
            base_prompt_path=base_prompt_path,
            temperature=temperature,
        ),
        env=env,
    )
    print(f"[MAIN] translate finished module={module}")


def run_score_and_emit_all_modules(env: Dict[str, str], *, modules: List[str]) -> None:
    """
    translate 3개 모듈이 모두 끝난 뒤,
    modules 전체를 대상으로 점수 계산 + best_overall(final_prompts) 생성
    """
    from src.pipelines.translate import (
        ScoreConfig,
        choose_target_langs,
        env_required_dataset_dirs,
        run_calculate_score,
        run_emit_final_prompts_global_best,
    )
    from src.metrics.cometkiwi import comet_default_model_name

    dataset = env["TARGET_DATASET"].strip()
    _prompts_dir, translated_dir, final_dir = env_required_dataset_dirs(env, dataset)

    target_langs = choose_target_langs(env)

    run_calculate_score(
        ScoreConfig(
            dataset=dataset,
            translated_dir=translated_dir,
            final_dir=final_dir,
            modules=modules,  # ✅ 전체 모듈 종합
            target_langs=target_langs,
            comet_model=env.get("COMET_MODEL_NAME", comet_default_model_name()),
        ),
        env=env,
    )

    run_emit_final_prompts_global_best(
        score_dir=final_dir,
        out_dir=final_dir / "final_prompts",
        tgt_langs=target_langs,
        modules=modules,  # ✅ 전체 모듈 종합
        env=env,
    )


def run_generate_single_model(*, model: str) -> None:
    """
    generate.py는 GEN_MODELS 환경변수를 읽어 모델 리스트를 구성하는 구조이므로,
    main에서 GEN_MODELS를 단일 모델로 바꿔가며 generate_main()을 여러 번 호출합니다.
    """
    from src.pipelines.generate import main as generate_main

    os.environ["GEN_MODELS"] = model  # ✅ 단일 모델 강제
    generate_main()


def parse_args() -> argparse.Namespace:
    p = argparse.ArgumentParser()

    p.add_argument(
        "--pipeline",
        choices=["translate", "score", "generate", "all"],
        default="all",
        help="Which stage(s) to run",
    )

    # 자주 바꾸는 env 오버라이드
    p.add_argument("--dataset", default=None, help="TARGET_DATASET override (e.g., CWEval)")
    p.add_argument("--translate_mode", default=None, help="TRANSLATE_MODE override: single|all")
    p.add_argument("--target_langs", default=None, help="TARGET_LANGUAGES override: comma-separated (e.g., ko,ja,fr)")
    p.add_argument("--translation_modules", default=None, help="TRANSLATION_MODULES override: comma-separated")
    p.add_argument("--gen_models", default=None, help="GEN_MODELS override: comma-separated (e.g., openai,deepseek)")
    p.add_argument("--resume", default=None, help="RESUME override: 1/0")

    return p.parse_args()


def main() -> None:
    _ensure_importable_project_root()
    load_dotenv()

    args = parse_args()

    # CLI overrides -> env 반영 (CLI > .env)
    _set_env_if_arg("TARGET_DATASET", args.dataset)
    _set_env_if_arg("TRANSLATE_MODE", args.translate_mode)
    _set_env_if_arg("TARGET_LANGUAGES", args.target_langs)
    _set_env_if_arg("TRANSLATION_MODULES", args.translation_modules)
    _set_env_if_arg("GEN_MODELS", args.gen_models)
    _set_env_if_arg("RESUME", args.resume)

    env = dict(os.environ)

    translation_modules = _get_translation_modules(env)
    generate_models = _get_generate_models(env)

    if args.pipeline == "translate":
        # ✅ deepseek -> openai -> nllb 순차 translate
        for m in translation_modules:
            print(f"[MAIN] translate start module={m}")
            run_translate_single_module(env, module=m)
            print(f"[MAIN] translate done  module={m}")
        return

    if args.pipeline == "score":
        # ✅ 전체 모듈 종합 스코어/emit (translate 결과가 이미 있어야 함)
        print(f"[MAIN] score/emit start modules={translation_modules}")
        run_score_and_emit_all_modules(env, modules=translation_modules)
        print("[MAIN] score/emit done")
        return

    if args.pipeline == "generate":
        # ✅ openai -> deepseek 순차 generate
        for gm in generate_models:
            print(f"[MAIN] generate start model={gm}")
            run_generate_single_model(model=gm)
            print(f"[MAIN] generate done  model={gm}")
        return

    # all
    # 1) translate: module 하나씩 순차
    for m in translation_modules:
        print(f"[MAIN] translate start module={m}")
        run_translate_single_module(env, module=m)
        print(f"[MAIN] translate done  module={m}")

    # 2) score/emit: 전체 모듈 종합
    print(f"[MAIN] score/emit start modules={translation_modules}")
    run_score_and_emit_all_modules(env, modules=translation_modules)
    print("[MAIN] score/emit done")

    # 3) generate: model 하나씩 순차 (openai -> deepseek)
    for gm in generate_models:
        print(f"[MAIN] generate start model={gm}")
        run_generate_single_model(model=gm)
        print(f"[MAIN] generate done  model={gm}")


if __name__ == "__main__":
    main()
