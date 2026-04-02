# -*- coding: utf-8 -*-
from __future__ import annotations

import json
import os
import random
import re
import time
from concurrent.futures import ThreadPoolExecutor, as_completed
from typing import Any, Dict, List, Optional

try:
    from openai import OpenAI, AzureOpenAI
except Exception:
    OpenAI = None  # type: ignore
    AzureOpenAI = None  # type: ignore


_SCORE_RE = re.compile(r"-?\d+(?:\.\d+)?")


def gemba_da_score_to_good(score: Optional[float]) -> Optional[float]:
    if score is None:
        return None
    x = max(0.0, min(100.0, float(score)))
    return x / 100.0


def gemba_da_supports_lang(lang_code: str, lang_map: Dict[str, str], env: Optional[Dict[str, str]] = None) -> bool:
    env = env or {}
    explicit_supported = {x.strip() for x in (env.get("GEMBA_DA_SUPPORTED_LANGS") or "").split(",") if x.strip()}
    explicit_unsupported = {x.strip() for x in (env.get("GEMBA_DA_UNSUPPORTED_LANGS") or "").split(",") if x.strip()}

    if lang_code in explicit_unsupported:
        return False
    if explicit_supported:
        return lang_code in explicit_supported
    return bool(lang_map.get(lang_code))


def _client_from_env(env: Dict[str, str]):
    api_type = (env.get("GEMBA_DA_API_TYPE") or "openai").strip().lower()
    timeout = float(env.get("GEMBA_DA_TIMEOUT_SEC", "60"))

    if api_type == "azure":
        if AzureOpenAI is None:
            raise ImportError("openai package with AzureOpenAI is required")
        return AzureOpenAI(
            api_key=env["GEMBA_DA_API_KEY"],
            api_version=env.get("GEMBA_DA_AZURE_API_VERSION", "2024-10-21"),
            azure_endpoint=env["GEMBA_DA_AZURE_ENDPOINT"],
            timeout=timeout,
        )

    if OpenAI is None:
        raise ImportError("openai package is required")

    base_url = (env.get("GEMBA_DA_BASE_URL") or "").strip() or None
    return OpenAI(api_key=env["GEMBA_DA_API_KEY"], base_url=base_url, timeout=timeout)


def _gemba_da_noref_prompt(source_lang_name: str, target_lang_name: str, source_seg: str, target_seg: str) -> str:
    return (
        f'Score the following translation from {source_lang_name} to {target_lang_name} '
        'on a continuous scale from 0 to 100, where a score of zero means "no meaning preserved" '
        'and score of one hundred means "perfect meaning and grammar".\n\n'
        f'{source_lang_name} source: "{source_seg}"\n'
        f'{target_lang_name} translation: "{target_seg}"\n'
        'Score:'
    )


def _parse_score(content: str) -> float:
    txt = (content or "").strip()
    try:
        obj = json.loads(txt)
        val = obj.get("score")
        if val is not None:
            return max(0.0, min(100.0, float(val)))
    except Exception:
        pass

    m = _SCORE_RE.search(txt)
    if not m:
        raise ValueError(f"Could not parse GEMBA-DA score from: {txt!r}")
    return max(0.0, min(100.0, float(m.group(0))))


def _score_one_segment(client, env: Dict[str, str], source_lang_name: str, target_lang_name: str, source_seg: str, target_seg: str) -> float:
    model = env.get("GEMBA_DA_MODEL_NAME", "gpt-4.1-mini")
    prompt = _gemba_da_noref_prompt(source_lang_name, target_lang_name, source_seg, target_seg)
    timeout = float(env.get("GEMBA_DA_TIMEOUT_SEC", "60"))

    resp = client.chat.completions.create(
        model=model,
        temperature=0.0,
        messages=[
            {"role": "system", "content": 'Return only JSON like {"score": 87}.'},
            {"role": "user", "content": prompt},
        ],
        response_format={"type": "json_object"},
        timeout=timeout,
    )
    content = resp.choices[0].message.content if resp.choices else ""
    return _parse_score(content or "")


def gemba_da_score_groups_mean(groups: List[Dict[str, Any]], env: Optional[Dict[str, str]] = None) -> Dict[str, Optional[float]]:
    env = dict(env or {})
    if not groups:
        return {}

    max_retry = int(env.get("GEMBA_DA_MAX_RETRY", "2"))
    workers = max(1, int(env.get("GEMBA_DA_WORKERS", "4")))

    client = _client_from_env(env)

    jobs: List[tuple[str, str, str, str, str]] = []
    for g in groups:
        key = str(g["key"])
        src_lang_name = str(g["source_lang_name"])
        tgt_lang_name = str(g["target_lang_name"])
        src_segments = list(g.get("src_segments") or [])
        mt_segments = list(g.get("mt_segments") or [])
        if len(src_segments) != len(mt_segments):
            raise ValueError(f"gemba_da group length mismatch: {key}")
        for s, t in zip(src_segments, mt_segments):
            jobs.append((key, src_lang_name, tgt_lang_name, s or "", t or ""))

    scores_by_key: Dict[str, List[float]] = {}

    def _run(job: tuple[str, str, str, str, str]) -> tuple[str, Optional[float]]:
        key, src_lang_name, tgt_lang_name, source_seg, target_seg = job
        for attempt in range(max_retry + 1):
            try:
                score = _score_one_segment(client, env, src_lang_name, tgt_lang_name, source_seg, target_seg)
                return key, score
            except Exception:
                if attempt >= max_retry:
                    return key, None
                time.sleep((0.8 * (attempt + 1)) + random.random() * 0.2)
        return key, None

    with ThreadPoolExecutor(max_workers=workers) as ex:
        futs = [ex.submit(_run, job) for job in jobs]
        for fut in as_completed(futs):
            key, score = fut.result()
            if score is None:
                continue
            scores_by_key.setdefault(key, []).append(float(score))

    out: Dict[str, Optional[float]] = {}
    for g in groups:
        key = str(g["key"])
        vals = scores_by_key.get(key, [])
        out[key] = (sum(vals) / len(vals)) if vals else None
    return out
