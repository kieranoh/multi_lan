# -*- coding: utf-8 -*-
from __future__ import annotations

import importlib.util
import json
import os
import subprocess
import sys
import tempfile
import time
import unicodedata
from pathlib import Path
from typing import Any, Dict, List, Optional

_MT5_SUPPORTED_LANGUAGE_NAMES = {
    "afrikaans", "albanian", "amharic", "arabic", "armenian", "azerbaijani", "basque",
    "belarusian", "bengali", "bulgarian", "burmese", "catalan", "cebuano", "chichewa",
    "chinese", "corsican", "czech", "danish", "dutch", "english", "esperanto", "estonian",
    "filipino", "finnish", "french", "galician", "georgian", "german", "greek", "gujarati",
    "haitian creole", "hausa", "hawaiian", "hebrew", "hindi", "hmong", "hungarian",
    "icelandic", "igbo", "indonesian", "irish", "italian", "japanese", "javanese", "kannada",
    "kazakh", "khmer", "korean", "kurdish", "kyrgyz", "lao", "latin", "latvian",
    "lithuanian", "luxembourgish", "macedonian", "malagasy", "malay", "malayalam", "maltese",
    "maori", "marathi", "mongolian", "nepali", "norwegian", "pashto", "persian", "polish",
    "portuguese", "punjabi", "romanian", "russian", "samoan", "scottish gaelic", "serbian",
    "shona", "sindhi", "sinhala", "slovak", "slovenian", "somali", "sotho", "spanish",
    "sundanese", "swahili", "swedish", "tajik", "tamil", "telugu", "thai", "turkish",
    "ukrainian", "urdu", "uzbek", "vietnamese", "welsh", "west frisian", "xhosa", "yiddish",
    "yoruba", "zulu",
}

_NAME_ALIASES = {
    "korean": "korean",
    "chinese simplified": "chinese",
    "simplified chinese": "chinese",
    "modern standard arabic": "arabic",
    "arabic": "arabic",
    "persian": "persian",
    "farsi": "persian",
    "scots gaelic": "scottish gaelic",
    "gaelic": "scottish gaelic",
}


def metricx24_default_model_name() -> str:
    return os.environ.get("METRICX24_MODEL_NAME", "google/metricx-24-hybrid-xxl-v2p6")


def _norm_name(name: str) -> str:
    s = unicodedata.normalize("NFKD", name or "")
    s = "".join(ch for ch in s if not unicodedata.combining(ch))
    s = s.lower().strip().replace("_", " ").replace("-", " ")
    s = " ".join(s.split())
    return _NAME_ALIASES.get(s, s)


def metricx24_supports_lang(lang_code: str, lang_map: Dict[str, str], env: Optional[Dict[str, str]] = None) -> bool:
    env = env or {}
    explicit_supported = {x.strip() for x in (env.get("METRICX24_SUPPORTED_LANGS") or "").split(",") if x.strip()}
    explicit_unsupported = {x.strip() for x in (env.get("METRICX24_UNSUPPORTED_LANGS") or "").split(",") if x.strip()}

    if lang_code in explicit_unsupported:
        return False
    if explicit_supported:
        return lang_code in explicit_supported

    lang_name = lang_map.get(lang_code, "")
    if not lang_name:
        return False
    return _norm_name(lang_name) in _MT5_SUPPORTED_LANGUAGE_NAMES


def metricx24_error_to_good(score: Optional[float]) -> Optional[float]:
    if score is None:
        return None
    x = max(0.0, min(25.0, float(score)))
    return 1.0 - (x / 25.0)


def _run_cmd(cmd: List[str], *, env: Optional[Dict[str, str]] = None, cwd: Optional[Path] = None) -> None:
    proc = subprocess.run(
        cmd,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
        env=env,
        cwd=str(cwd) if cwd else None,
        check=False,
    )
    if proc.returncode != 0:
        raise RuntimeError(
            f"Command failed (rc={proc.returncode}): {' '.join(cmd)}\n"
            f"STDOUT:\n{proc.stdout[:4000]}\nSTDERR:\n{proc.stderr[:4000]}"
        )


def _metricx_runtime_extra_env(env: Dict[str, str]) -> Dict[str, str]:
    """
    metricx24 모듈이 없으면:
    1) repo clone
    2) requirements 설치
    3) subprocess 실행 시 PYTHONPATH에 repo 추가
    """
    if importlib.util.find_spec("metricx24") is not None:
        return {}

    repo_dir = Path(
        env.get(
            "METRICX24_REPO_DIR",
            str(Path.home() / ".cache" / "metricx_repo")
        )
    ).expanduser().resolve()

    repo_dir.parent.mkdir(parents=True, exist_ok=True)

    if not repo_dir.exists():
        _run_cmd(["git", "clone", "https://github.com/google-research/metricx.git", str(repo_dir)])
    else:
        try:
            _run_cmd(["git", "-C", str(repo_dir), "pull", "--ff-only"])
        except Exception:
            pass

    req = repo_dir / "requirements.txt"
    if req.exists():
        _run_cmd([sys.executable, "-m", "pip", "install", "-r", str(req)])

    extra_env: Dict[str, str] = {}
    cur_pp = os.environ.get("PYTHONPATH", "")
    extra_env["PYTHONPATH"] = str(repo_dir) + (os.pathsep + cur_pp if cur_pp else "")
    return extra_env


def _build_cmd(input_path: Path, output_path: Path, env: Dict[str, str]) -> List[str]:
    tokenizer = env.get("METRICX24_TOKENIZER", "google/mt5-xl").strip()
    model_name = env.get("METRICX24_MODEL_NAME", metricx24_default_model_name()).strip()
    max_input_length = int(env.get("METRICX24_MAX_INPUT_LENGTH", "1536"))
    batch_size = int(env.get("METRICX24_BATCH_SIZE", "1"))
    python_bin = env.get("METRICX24_PYTHON_BIN", sys.executable)

    return [
        python_bin,
        "-m",
        "metricx24.predict",
        "--tokenizer", tokenizer,
        "--model_name_or_path", model_name,
        "--max_input_length", str(max_input_length),
        "--batch_size", str(batch_size),
        "--input_file", str(input_path),
        "--output_file", str(output_path),
        "--qe",
    ]


def metricx24_score_groups_mean(groups: List[Dict[str, Any]], env: Optional[Dict[str, str]] = None) -> Dict[str, Optional[float]]:
    env = dict(env or {})
    if not groups:
        return {}

    rows: List[Dict[str, str]] = []
    spans: Dict[str, tuple[int, int]] = {}

    for g in groups:
        key = str(g["key"])
        src_segments = list(g.get("src_segments") or [])
        mt_segments = list(g.get("mt_segments") or [])
        if len(src_segments) != len(mt_segments):
            raise ValueError(f"metricx24 group length mismatch: {key}")

        start = len(rows)
        for s, t in zip(src_segments, mt_segments):
            rows.append({
                "source": s or "",
                "hypothesis": t or "",
                "reference": "",
            })
        spans[key] = (start, len(rows))

    if not rows:
        return {str(g["key"]): None for g in groups}

    with tempfile.TemporaryDirectory(prefix="metricx24_") as tmpdir:
        tmp = Path(tmpdir)
        input_path = tmp / "input.jsonl"
        output_path = tmp / "output.jsonl"
        log_path = tmp / "stderr.log"

        with input_path.open("w", encoding="utf-8") as f:
            for row in rows:
                f.write(json.dumps(row, ensure_ascii=False) + "\n")

        sub_env = os.environ.copy()
        sub_env.update(env)
        sub_env.update(_metricx_runtime_extra_env(env))

        sub_env.setdefault("TOKENIZERS_PARALLELISM", "false")
        sub_env.setdefault("TRANSFORMERS_VERBOSITY", "error")

        if env.get("HF_HOME"):
            sub_env["HF_HOME"] = env["HF_HOME"]
        if env.get("TORCH_HOME"):
            sub_env["TORCH_HOME"] = env["TORCH_HOME"]

        if env.get("METRICX24_CUDA_VISIBLE_DEVICES"):
            sub_env["CUDA_VISIBLE_DEVICES"] = env["METRICX24_CUDA_VISIBLE_DEVICES"]
        elif env.get("METRICX24_DEVICE", "").startswith("cuda:"):
            sub_env["CUDA_VISIBLE_DEVICES"] = env["METRICX24_DEVICE"].split(":", 1)[1]

        if env.get("METRICX24_PROTOCOL_BUFFERS_PYTHON_IMPLEMENTATION"):
            sub_env["PROTOCOL_BUFFERS_PYTHON_IMPLEMENTATION"] = env["METRICX24_PROTOCOL_BUFFERS_PYTHON_IMPLEMENTATION"]

        cmd = _build_cmd(input_path, output_path, env)
        t0 = time.perf_counter()
        proc = subprocess.run(
            cmd,
            env=sub_env,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
            check=False,
        )
        dt = time.perf_counter() - t0
        log_path.write_text(proc.stderr or "", encoding="utf-8")

        if proc.returncode != 0:
            raise RuntimeError(
                f"MetricX-24 inference failed (rc={proc.returncode}) after {dt:.2f}s. "
                f"See stderr: {log_path}\n{proc.stderr[:4000]}"
            )

        preds: List[Optional[float]] = []
        with output_path.open("r", encoding="utf-8") as f:
            for line in f:
                line = line.strip()
                if not line:
                    continue
                obj = json.loads(line)
                pred = obj.get("prediction")
                preds.append(None if pred is None else float(pred))

    out: Dict[str, Optional[float]] = {}
    for key, (start, end) in spans.items():
        chunk = [x for x in preds[start:end] if x is not None]
        out[key] = (sum(chunk) / len(chunk)) if chunk else None
    return out