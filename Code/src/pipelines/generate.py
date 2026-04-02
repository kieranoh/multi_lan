# -*- coding: utf-8 -*-
from __future__ import annotations

import os
import time
import json
import random
from dataclasses import dataclass
from pathlib import Path
from typing import Any, Dict, List, Optional, Tuple
from concurrent.futures import ThreadPoolExecutor, as_completed
from threading import Lock

from dotenv import load_dotenv
from tqdm import tqdm

from src.io.reader import read_jsonl
from src.io.writer import append_jsonl

try:
    from openai import OpenAI
except Exception:
    OpenAI = None  # type: ignore


# -------------------------
# ENV helpers
# -------------------------

def _env_list(key: str, default: str = "") -> List[str]:
    v = os.environ.get(key, default)
    return [x.strip() for x in v.split(",") if x.strip()]


def _env_flag(key: str, default: str = "0") -> bool:
    v = str(os.environ.get(key, default)).strip().lower()
    return v in ("1", "true", "yes", "y", "on")


def _env_int(key: str, default: int) -> int:
    try:
        return int(str(os.environ.get(key, default)).strip())
    except Exception:
        return default


def _env_float(key: str, default: float) -> float:
    try:
        return float(str(os.environ.get(key, default)).strip())
    except Exception:
        return default


def _sleep_backoff(attempt: int, base: float, cap: float) -> None:
    t = min(cap, base * (attempt + 1))
    time.sleep(t + random.random() * 0.2)


# -------------------------
# Output helpers
# -------------------------

def write_text(path: Path, text: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text, encoding="utf-8")


def strip_triple_backticks(s: str) -> str:
    t = s.strip()
    if "```" not in t:
        return t
    a = t.find("```")
    if a < 0:
        return t
    b = t.find("```", a + 3)
    if b < 0:
        return t
    inner = t[a + 3 : b]
    lines = inner.splitlines()
    # drop optional language label on first line
    if lines and lines[0].strip() and " " not in lines[0].strip():
        lines = lines[1:]
    out = "\n".join(lines).strip()
    return out or t


def lang_to_ext(lang: str) -> str:
    l = lang.strip().lower()
    m = {
        "c": "c",
        "cc": "cpp",
        "cpp": "cpp",
        "cxx": "cpp",
        "h": "h",
        "hpp": "hpp",

        "py": "py",
        "python": "py",

        "go": "go",
        "java": "java",

        "js": "js",
        "javascript": "js",

        "ts": "ts",
        "typescript": "ts",

        "rs": "rs",
        "rust": "rs",

        "cs": "cs",
        "csharp": "cs",

        "php": "php",
    }
    return m.get(l, l)


def _task_to_short_name(task: str) -> str:
    """
    Example:
      cwe_022_0_c  -> cwe022_0
      cwe_078_12_py -> cwe078_12
    """
    t = str(task).strip()
    parts = t.split("_")
    if len(parts) >= 3 and parts[0].lower() == "cwe":
        num = parts[1]
        idx = parts[2]
        return f"cwe{num}_{idx}"
    if len(parts) >= 2:
        return "_".join(parts[:-1])
    return t


def _is_task_done(out_dir: Path, short_task: str, ext: str, n_samples: int) -> bool:
    """
    이어하기 핵심:
    - n_samples 개가 모두 존재하면 DONE 처리
    - 하나라도 없으면 이어서 생성
    """
    for k in range(n_samples):
        if not (out_dir / f"{short_task}_{k}.{ext}").exists():
            return False
    return True


# -------------------------
# LLM client (OpenAI SDK; DeepSeek uses base_url)
# -------------------------

@dataclass
class GenClient:
    name: str          # "openai" or "deepseek"
    model: str
    api_key: str
    base_url: Optional[str] = None

    def _client(self):
        if OpenAI is None:
            raise ImportError("openai package is not available. Install: pip install openai")
        if self.base_url:
            return OpenAI(api_key=self.api_key, base_url=self.base_url)
        return OpenAI(api_key=self.api_key)

    @classmethod
    def from_env(cls, name: str) -> "GenClient":
        n = name.strip().lower()
        if n == "openai":
            api_key = os.environ["OPENAI_API_KEY"]
            model = os.environ.get("OPENAI_MODEL_NAME", "gpt-4o-mini")
            base_url = os.environ.get("OPENAI_BASE_URL") or None
            return cls(name="openai", model=model, api_key=api_key, base_url=base_url)

        if n == "deepseek":
            api_key = os.environ["DEEPSEEK_API_KEY"]
            model = os.environ.get("DEEPSEEK_MODEL_NAME", "deepseek-chat")
            base_url = os.environ.get("DEEPSEEK_BASE_URL", "https://api.deepseek.com")
            return cls(name="deepseek", model=model, api_key=api_key, base_url=base_url)

        raise ValueError(f"Unsupported GEN model: {name}")

    def generate_n(
        self,
        *,
        system: str,
        user: str,
        n: int,
        temperature: float,
        max_completion_tokens: int,
    ) -> List[str]:
        client = self._client()
        resp = client.chat.completions.create(
            model=self.model,
            messages=[
                {"role": "system", "content": system},
                {"role": "user", "content": user},
            ],
            n=int(n),
            temperature=float(temperature),
            max_completion_tokens=int(max_completion_tokens),
        )
        outs: List[str] = []
        for ch in resp.choices:
            outs.append((ch.message.content or "").strip())
        if len(outs) < n:
            outs.extend([""] * (n - len(outs)))
        return outs[:n]


# -------------------------
# Load BEST templates + BEST prompts
# -------------------------

def _resolve_target_langs(final_prompts_root: Path) -> List[str]:
    mode = str(os.environ.get("TRANSLATE_MODE", "single")).strip().lower()
    if mode == "all":
        if not final_prompts_root.exists():
            return []
        return sorted([p.name for p in final_prompts_root.iterdir() if p.is_dir()])
    langs = [x for x in _env_list("TARGET_LANGUAGES", "ko") if x.strip() and x.strip() != "en"]
    return langs


def load_best_templates(best_overall_dir: Path) -> Dict[Tuple[str, str], Dict[str, str]]:
    path = best_overall_dir / "gen_prompt_templates_en.jsonl"
    recs = read_jsonl(path)
    if not recs:
        raise FileNotFoundError(f"Missing template file: {path}")

    out: Dict[Tuple[str, str], Dict[str, str]] = {}
    for r in recs:
        task = str(r.get("task", "")).strip()
        code_lang = str(r.get("lang", "")).strip()
        prompt = r.get("prompt")
        if not task or not code_lang:
            continue
        if not isinstance(prompt, str) or not prompt.strip():
            raise ValueError(f"Template missing best 'prompt': {path} task={task} lang={code_lang}")

        parts = task.split("_")
        if len(parts) < 3:
            continue
        ppt_type = parts[1].strip().lower()  # direct/secure/compl

        out[(ppt_type, code_lang)] = {
            "system": prompt.strip(),
            "user_prefix": "",
        }
    return out


def load_best_task_prompts(best_overall_dir: Path) -> List[Tuple[str, str, str, str]]:
    items: List[Tuple[str, str, str, str]] = []
    files = sorted(best_overall_dir.glob("prompts_*_en.jsonl"))
    if not files:
        raise FileNotFoundError(f"No prompts_*_en.jsonl in: {best_overall_dir}")

    for p in files:
        recs = read_jsonl(p)
        for r in recs:
            task = str(r.get("task", "")).strip()
            code_lang = str(r.get("lang", "")).strip()
            best = r.get("prompt")
            if not task or not code_lang:
                continue
            if not isinstance(best, str) or not best.strip():
                raise ValueError(f"Missing best 'prompt' in: {p} task={task} lang={code_lang}")
            items.append((p.name, task, code_lang, best))
    if not items:
        raise RuntimeError(f"All prompts_*_en.jsonl are empty in: {best_overall_dir}")
    return items


# -------------------------
# Worker task
# -------------------------

def _process_one_task(
    *,
    client: GenClient,
    dataset: str,
    tgt: str,
    gm: str,
    ppt_type: str,
    src_file: str,
    task: str,
    code_lang: str,
    best_code_prompt: str,
    templates: Dict[Tuple[str, str], Dict[str, str]],
    code_root: Path,
    n_samples: int,
    temperature: float,
    max_completion_tokens: int,
    strip_fences: bool,
    resume: bool,
    retry_max: int,
    backoff0: float,
    backoff_cap: float,
    gen_log: Path,
    log_lock: Lock,
) -> Dict[str, Any]:
    tpl_rec = templates.get((ppt_type, code_lang))
    if tpl_rec is None:
        raise RuntimeError(f"Missing template for ppt={ppt_type} lang={code_lang} (tgt={tgt})")

    system_msg = tpl_rec["system"]
    user_msg = (tpl_rec.get("user_prefix") or "") + best_code_prompt

    ext = lang_to_ext(code_lang)
    short_task = _task_to_short_name(task)

    out_dir = code_root / tgt / gm / code_lang / task
    out_dir.mkdir(parents=True, exist_ok=True)

    # 이어하기(완료된 task는 통째로 skip)
    if resume and _is_task_done(out_dir, short_task, ext, n_samples):
        return {
            "task": task,
            "task_short": short_task,
            "lang": code_lang,
            "status": "skipped_done",
        }

    attempt = 0
    while True:
        try:
            t0 = time.perf_counter()
            outs = client.generate_n(
                system=system_msg,
                user=user_msg,
                n=n_samples,
                temperature=temperature,
                max_completion_tokens=max_completion_tokens,
            )
            dt = time.perf_counter() - t0

            for k, text in enumerate(outs):
                out_path = out_dir / f"{short_task}_{k}.{ext}"
                # 이어하기: 이미 있는 샘플은 건드리지 않음
                if resume and out_path.exists():
                    continue
                if strip_fences:
                    text = strip_triple_backticks(text)
                write_text(out_path, text)

            with log_lock:
                append_jsonl(
                    gen_log,
                    {
                        "ts": time.time(),
                        "duration_sec": dt,
                        "retry_attempts": attempt,
                        "dataset": dataset,
                        "target_lang": tgt,
                        "gen_model": gm,
                        "model_name": client.model,
                        "ppt_type": ppt_type,
                        "src_prompts_file": src_file,
                        "task": task,
                        "task_short": short_task,
                        "lang": code_lang,
                        "n_samples": n_samples,
                    },
                )

            return {
                "task": task,
                "task_short": short_task,
                "lang": code_lang,
                "status": "ok",
                "duration_sec": dt,
                "retry_attempts": attempt,
            }

        except Exception as e:
            if retry_max >= 0 and attempt >= retry_max:
                raise RuntimeError(
                    f"[GEN FAIL] tgt={tgt} gm={gm} task={task} lang={code_lang} src={src_file} last={e}"
                ) from e
            _sleep_backoff(attempt, backoff0, backoff_cap)
            attempt += 1


# -------------------------
# Main
# -------------------------

def main() -> None:
    load_dotenv()

    dataset = str(os.environ.get("TARGET_DATASET", "CWEval")).strip()
    ds = dataset.upper()

    final_dir = Path(os.environ[f"{ds}_FINAL_TRANSLATED_DIR"]).resolve()
    final_prompts_root = final_dir / "final_prompts"

    code_root = Path(os.environ.get("CODE_OUTPUT_DIR", "data/code")).resolve()
    code_root.mkdir(parents=True, exist_ok=True)

    # generation settings
    gen_models = _env_list("GEN_MODELS", "openai,deepseek")
    ppt_type = str(os.environ.get("CWEVAL_PPT_TYPE", "direct")).strip().lower()
    if ppt_type not in ("direct", "secure", "compl"):
        raise ValueError("CWEVAL_PPT_TYPE must be one of: direct, secure, compl")

    n_samples = _env_int("GEN_SAMPLES_PER_PROMPT", 1)
    temperature = _env_float("GEN_TEMPERATURE", 0.8)
    max_completion_tokens = _env_int("GEN_MAX_COMPLETION_TOKENS", 2048)

    strip_fences = _env_flag("STRIP_CODE_FENCES", "1")
    resume = _env_flag("RESUME", "1")

    # NEW: worker 기반 병렬 처리 수 (기본 1 = 기존과 동일)
    gen_workers = _env_int("GEN_WORKERS", 1)
    if gen_workers < 1:
        gen_workers = 1

    # 기존 sharding 로직은 유지
    shard_count = _env_int("GEN_SHARD_COUNT", 1)
    shard_index = _env_int("GEN_SHARD_INDEX", 0)
    if shard_count < 1:
        shard_count = 1
    if shard_index < 0 or shard_index >= shard_count:
        raise ValueError(f"GEN_SHARD_INDEX must be in [0, GEN_SHARD_COUNT). got {shard_index}/{shard_count}")

    retry_max = _env_int("GEN_RETRY_MAX", -1)  # -1 infinite
    backoff0 = _env_float("GEN_RETRY_BACKOFF_SEC", 1.0)
    backoff_cap = _env_float("GEN_RETRY_BACKOFF_MAX_SEC", 30.0)

    gen_log = code_root / "_logs" / "generate.jsonl"
    log_lock = Lock()

    target_langs = _resolve_target_langs(final_prompts_root)
    if not target_langs:
        raise RuntimeError(f"No target languages resolved. final_prompts_root={final_prompts_root}")

    for tgt in target_langs:
        best_overall_dir = final_prompts_root / tgt / "best_overall"
        if not best_overall_dir.exists():
            raise FileNotFoundError(f"Missing best_overall dir: {best_overall_dir}")

        templates = load_best_templates(best_overall_dir)
        tasks = load_best_task_prompts(best_overall_dir)

        for gm in gen_models:
            client = GenClient.from_env(gm)

            desc = (
                f"GEN {dataset} tgt={tgt} gm={gm} ppt={ppt_type} "
                f"shard={shard_index}/{shard_count} workers={gen_workers}"
            )

            # 기존 sharding 유지: 먼저 대상 task만 추립니다.
            selected_tasks: List[Tuple[str, str, str, str]] = []
            for global_i, item in enumerate(tasks):
                if (global_i % shard_count) != shard_index:
                    continue
                selected_tasks.append(item)

            pbar = tqdm(total=len(selected_tasks), desc=desc, unit="task", dynamic_ncols=True)

            with ThreadPoolExecutor(max_workers=gen_workers) as ex:
                futures = []
                for src_file, task, code_lang, best_code_prompt in selected_tasks:
                    futures.append(
                        ex.submit(
                            _process_one_task,
                            client=client,
                            dataset=dataset,
                            tgt=tgt,
                            gm=gm,
                            ppt_type=ppt_type,
                            src_file=src_file,
                            task=task,
                            code_lang=code_lang,
                            best_code_prompt=best_code_prompt,
                            templates=templates,
                            code_root=code_root,
                            n_samples=n_samples,
                            temperature=temperature,
                            max_completion_tokens=max_completion_tokens,
                            strip_fences=strip_fences,
                            resume=resume,
                            retry_max=retry_max,
                            backoff0=backoff0,
                            backoff_cap=backoff_cap,
                            gen_log=gen_log,
                            log_lock=log_lock,
                        )
                    )

                for fut in as_completed(futures):
                    # 원래처럼 실패 시 전체 실행을 중단하도록 fut.result()에서 예외를 그대로 올립니다.
                    fut.result()
                    pbar.update(1)

            pbar.close()

    print("[DONE] generate finished.")


if __name__ == "__main__":
    main()