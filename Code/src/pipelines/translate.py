#!/usr/bin/env python3
# -*- coding: utf-8 -*-
from __future__ import annotations

from dotenv import load_dotenv
load_dotenv()

import argparse
import os
import warnings

# Reduce noisy warnings/logs from HF/Lightning during scoring
os.environ.setdefault('PYTHONWARNINGS', 'ignore')
os.environ.setdefault('TOKENIZERS_PARALLELISM', 'false')
os.environ.setdefault('TRANSFORMERS_VERBOSITY', 'error')
# HuggingFace symlink warning (mostly on Windows)
os.environ.setdefault('HF_HUB_DISABLE_SYMLINKS_WARNING', '1')
warnings.filterwarnings('ignore')

import threading
import time
from concurrent.futures import ThreadPoolExecutor, as_completed
from dataclasses import dataclass
from pathlib import Path
from typing import Any, Dict, List, Tuple, Optional

from tqdm import tqdm

from src.io.reader import read_jsonl, list_en_jsonl_files
from src.io.writer import write_jsonl, append_jsonl
from src.metrics.bertscore import bertscore_mean_f1
from src.metrics.cometkiwi import cometkiwi_mean, comet_default_model_name
import src.metrics.cometkiwi as cometkiwi_mod
from src.postprocess.preserve_code import extract_code_and_prompts, fill_code_template
from src.translators.base import build_translator, get_num_variants, compute_cost_usd


# ─────────────────────────────────────────────────────────────
# Helpers
# ─────────────────────────────────────────────────────────────

def _env_flag(env: Dict[str, str], key: str, default: str = "0") -> bool:
    v = str(env.get(key, default)).strip().lower()
    return v in ("1", "true", "yes", "y", "on")


def _load_done_tasks(path: Path) -> set[str]:
    """Best-effort: read jsonl and return set of rec['task'] that exist."""
    done: set[str] = set()
    if not path.exists():
        return done
    try:
        for r in read_jsonl(path):
            t = r.get("task")
            if isinstance(t, str) and t:
                done.add(t)
    except Exception:
        # partially written/corrupt file -> ignore
        pass
    return done


def _set_postfix_clean(pbar: tqdm, s: str) -> None:
    """
    tqdm.set_postfix_str() sometimes prefixes ', ' depending on formatting.
    Writing to pbar.postfix avoids that.
    """
    pbar.postfix = s
    pbar.refresh()


def _safe_all_update(
    all_pbar: Optional[tqdm],
    all_lock: Optional[threading.Lock],
    n: int,
) -> None:
    if all_pbar is None or n <= 0:
        return
    if all_lock is not None:
        with all_lock:
            all_pbar.update(n)
    else:
        all_pbar.update(n)


def _ensure_parent(path: Path) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)


def _append_or_write_jsonl(path: Path, recs: List[Dict[str, Any]], *, resume: bool) -> None:
    """
    If resume and file exists -> append line-by-line.
    Else -> overwrite whole file.
    """
    _ensure_parent(path)
    if resume and path.exists():
        for r in recs:
            append_jsonl(path, r)
    else:
        write_jsonl(path, recs)


# ─────────────────────────────────────────────────────────────
# Configs
# ─────────────────────────────────────────────────────────────

@dataclass
class TranslateConfig:
    dataset: str
    prompts_dir: Path
    translated_dir: Path
    modules: List[str]
    target_langs: List[str]
    base_prompt_path: Path
    temperature: float


@dataclass
class ScoreConfig:
    dataset: str
    translated_dir: Path
    final_dir: Path
    modules: List[str]
    target_langs: List[str]
    comet_model: str


# ─────────────────────────────────────────────────────────────
# Translate stage (module-parallel)
# ─────────────────────────────────────────────────────────────

def run_translate_for_module(
    cfg: TranslateConfig,
    env: Dict[str, str],
    module_name: str,
    *,
    pos_base: int = 0,
    all_pbar: Optional[tqdm] = None,
    all_lock: Optional[threading.Lock] = None,
) -> None:
    translator = build_translator(module_name, env, cfg.base_prompt_path)

    log_path = cfg.translated_dir / "_logs" / "translate_cost_time.jsonl"
    stage1_log_path = cfg.translated_dir / "_logs" / "translate_stage1.jsonl"

    resume = _env_flag(env, "RESUME", "0")

    try:
        bt_workers = max(1, int(env.get("BT_PARALLELISM", "1")))
    except Exception:
        bt_workers = 1

    # NLLB tokenizer/model are not thread-safe across BT threads
    if module_name == "nllb":
        bt_workers = 1

    in_files = list_en_jsonl_files(cfg.prompts_dir)
    if not in_files:
        print(f"[WARN] No *en.jsonl files in: {cfg.prompts_dir}")
        return

    for in_path in in_files:
        recs = read_jsonl(in_path)

        for tgt_lang in cfg.target_langs:
            n_variants = get_num_variants(module_name, env)

            s1_path = cfg.translated_dir / "_stage1_forward" / tgt_lang / module_name / in_path.name
            meta_path = cfg.translated_dir / "_stage2_meta" / tgt_lang / module_name / in_path.name
            out_path = cfg.translated_dir / tgt_lang / module_name / in_path.name

            # Create dirs always. Delete files only when not RESUME.
            for p in (s1_path, meta_path, out_path):
                p.parent.mkdir(parents=True, exist_ok=True)
                if (not resume) and p.exists():
                    p.unlink()

            # Done sets for resume
            done_s1 = _load_done_tasks(s1_path) if resume else set()
            done_out = _load_done_tasks(out_path) if resume else set()

            # Pre-advance ALL progress for already-done tasks (resume mode)
            if resume:
                _safe_all_update(all_pbar, all_lock, len(done_s1) * n_variants)   # stage1 already done
                _safe_all_update(all_pbar, all_lock, len(done_out) * n_variants)  # stage2 already done

            # ─────────────────────────────
            # Stage 1: forward translate (CALL-level progress)
            # ─────────────────────────────
            total_fw_calls = len(recs) * n_variants
            short_desc1 = f"S1 {in_path.name} {tgt_lang}/{module_name} n={n_variants}"

            pbar_fw = tqdm(
                total=total_fw_calls,
                desc=short_desc1,
                unit="call",
                dynamic_ncols=True,
                position=pos_base,
                leave=True,
                bar_format="{desc}: {n_fmt}/{total_fmt} [{elapsed}<{remaining}, {rate_fmt}] | {postfix}",
            )

            if resume and done_s1:
                pbar_fw.update(min(len(done_s1) * n_variants, total_fw_calls))

            for prompt_idx, rec in enumerate(recs, start=1):
                task = rec["task"]
                lang = rec["lang"]
                prompt_en_full = rec["prompt"]

                if resume and task in done_s1:
                    continue

                # ─────────────────────────────────────────────────────
                # [ADD] Special-case: gen_prompt_templates_en.jsonl
                #   - translate the whole rec["prompt"] directly (1 segment)
                #   - bypass comment extraction
                # ─────────────────────────────────────────────────────
                if in_path.name == "gen_prompt_templates_en.jsonl":
                    code_template = "{PROMPT_1}"
                    prompt_txt = str(prompt_en_full).strip()
                    prompts_en = [prompt_txt] if prompt_txt else []
                else:
                    code_template, prompts_en = extract_code_and_prompts(prompt_en_full, lang)

                call_end = prompt_idx * n_variants
                tqdm.write(
                    f"[DBG] task={task} lang={lang} segments={len(prompts_en)} "
                    f"calls={call_end-n_variants+1}-{call_end}/{total_fw_calls}"
                )
                _set_postfix_clean(
                    pbar_fw,
                    f"{call_end}/{total_fw_calls} p={prompt_idx}/{len(recs)} s={len(prompts_en)}",
                )

                t0 = time.perf_counter()
                if prompts_en:
                    segs_by_variant, meta_fw = translator.translate_prompt_variants(
                        segments=prompts_en,
                        src_lang="en",
                        tgt_lang=tgt_lang,
                        n_variants=n_variants,
                        temperature=cfg.temperature,
                    )
                else:
                    segs_by_variant = [[] for _ in range(n_variants)]
                    meta_fw = {
                        "prompt_tokens": 0,
                        "completion_tokens": 0,
                        "elapsed_sec": 0.0,
                        "variant_calls": 0,
                        "variant_parallelism": 1,
                    }
                elapsed_fw_total = time.perf_counter() - t0

                pbar_fw.update(n_variants)
                _safe_all_update(all_pbar, all_lock, n_variants)

                s1_rec: Dict[str, Any] = {
                    "task": task,
                    "lang": lang,
                    "target_lang": tgt_lang,
                    "module": module_name,
                    "n_variants": n_variants,
                    "prompt_en": prompt_en_full,
                    "code": code_template,
                    "prompts_en": prompts_en,
                    "fw_segments_by_variant": segs_by_variant,
                    "meta_fw": meta_fw,
                    "elapsed_sec_fw_total": float(elapsed_fw_total),
                }
                append_jsonl(s1_path, s1_rec)

                fw_pt = int(meta_fw.get("prompt_tokens", 0) or 0)
                fw_ct = int(meta_fw.get("completion_tokens", 0) or 0)
                fw_cost = compute_cost_usd(module_name, fw_pt, fw_ct, env)

                append_jsonl(
                    stage1_log_path,
                    {
                        "ts": time.time(),
                        "stage": "stage1_forward",
                        "dataset": cfg.dataset,
                        "file": in_path.name,
                        "module": module_name,
                        "target_lang": tgt_lang,
                        "task": task,
                        "lang": lang,
                        "n_variants": n_variants,
                        "n_segments": len(prompts_en),
                        "variant_calls": int(meta_fw.get("variant_calls", n_variants) or n_variants),
                        "variant_parallelism": int(meta_fw.get("variant_parallelism", 1) or 1),
                        "elapsed_sec_fw_total": float(elapsed_fw_total),
                        "elapsed_sec_fw_api_sum": float(meta_fw.get("elapsed_sec", 0.0) or 0.0),
                        "prompt_tokens_fw": fw_pt,
                        "completion_tokens_fw": fw_ct,
                        "cost_usd_fw": fw_cost,
                    },
                )

            pbar_fw.close()

            # ─────────────────────────────
            # Stage 2: back-translate from stage1 cache (CALL-level progress)
            # ─────────────────────────────
            s1_recs = read_jsonl(s1_path)
            total_bt_calls = len(s1_recs) * n_variants
            short_desc2 = f"S2 {in_path.name} bt {module_name}"

            pbar_bt = tqdm(
                total=total_bt_calls,
                desc=short_desc2,
                unit="call",
                dynamic_ncols=True,
                position=pos_base + 1,
                leave=True,
                bar_format="{desc}: {n_fmt}/{total_fmt} [{elapsed}<{remaining}, {rate_fmt}] | {postfix}",
            )

            if resume and done_out:
                pbar_bt.update(min(len(done_out) * n_variants, total_bt_calls))

            for prompt_idx, s1_rec in enumerate(s1_recs, start=1):
                task = s1_rec["task"]
                lang = s1_rec["lang"]
                prompt_en_full = s1_rec["prompt_en"]
                code_template = s1_rec["code"]
                prompts_en: List[str] = s1_rec["prompts_en"]
                segs_by_variant: List[List[str]] = s1_rec["fw_segments_by_variant"]
                meta_fw = s1_rec.get("meta_fw", {"prompt_tokens": 0, "completion_tokens": 0, "elapsed_sec": 0.0})

                if resume and task in done_out:
                    continue

                call_end = prompt_idx * n_variants
                _set_postfix_clean(pbar_bt, f"{call_end}/{total_bt_calls} p={prompt_idx}/{len(s1_recs)}")

                t0 = time.perf_counter()

                bt_by_variant: List[List[str]] = [[] for _ in range(n_variants)]
                meta_bt_sum = {"prompt_tokens": 0, "completion_tokens": 0, "elapsed_sec": 0.0}

                if prompts_en:

                    def bt_one(i: int):
                        bt_variant, meta_bt = translator.translate_prompt_variants(
                            segments=segs_by_variant[i],
                            src_lang=tgt_lang,
                            tgt_lang="en",
                            n_variants=1,
                            temperature=0.0,
                        )
                        return i, bt_variant[0], meta_bt

                    if bt_workers > 1 and n_variants > 1:
                        with ThreadPoolExecutor(max_workers=min(bt_workers, n_variants)) as ex:
                            futs = [ex.submit(bt_one, i) for i in range(n_variants)]
                            for fut in as_completed(futs):
                                i, bt_segs, meta_bt = fut.result()
                                bt_by_variant[i] = bt_segs
                                meta_bt_sum["prompt_tokens"] += int(meta_bt.get("prompt_tokens", 0) or 0)
                                meta_bt_sum["completion_tokens"] += int(meta_bt.get("completion_tokens", 0) or 0)
                                meta_bt_sum["elapsed_sec"] += float(meta_bt.get("elapsed_sec", 0.0) or 0.0)
                    else:
                        for i in range(n_variants):
                            i2, bt_segs, meta_bt = bt_one(i)
                            bt_by_variant[i2] = bt_segs
                            meta_bt_sum["prompt_tokens"] += int(meta_bt.get("prompt_tokens", 0) or 0)
                            meta_bt_sum["completion_tokens"] += int(meta_bt.get("completion_tokens", 0) or 0)
                            meta_bt_sum["elapsed_sec"] += float(meta_bt.get("elapsed_sec", 0.0) or 0.0)

                    prompt_variants: List[str] = [
                        fill_code_template(code_template, segs_by_variant[i]) for i in range(n_variants)
                    ]
                else:
                    prompt_variants = [prompt_en_full for _ in range(n_variants)]

                elapsed_total = time.perf_counter() - t0

                pbar_bt.update(n_variants)
                _safe_all_update(all_pbar, all_lock, n_variants)

                meta_rec: Dict[str, Any] = {
                    "task": task,
                    "lang": lang,
                    "target_lang": tgt_lang,
                    "module": module_name,
                    "n_variants": n_variants,
                    "prompt_en": prompt_en_full,
                    "code": code_template,
                    "prompts_en": prompts_en,
                }
                for i in range(n_variants):
                    meta_rec[f"prompt_{i+1}"] = prompt_variants[i]
                    meta_rec[f"prompt_{i+1}_segments"] = segs_by_variant[i]
                    meta_rec[f"prompt_{i+1}_bt_segments_en"] = bt_by_variant[i]
                append_jsonl(meta_path, meta_rec)

                out_rec: Dict[str, Any] = {"task": task, "lang": lang}
                for i in range(n_variants):
                    out_rec[f"prompt_{i+1}"] = prompt_variants[i]
                append_jsonl(out_path, out_rec)

                fw_pt = int(meta_fw.get("prompt_tokens", 0) or 0)
                fw_ct = int(meta_fw.get("completion_tokens", 0) or 0)
                bt_pt = int(meta_bt_sum.get("prompt_tokens", 0) or 0)
                bt_ct = int(meta_bt_sum.get("completion_tokens", 0) or 0)
                cost = compute_cost_usd(module_name, fw_pt + bt_pt, fw_ct + bt_ct, env)

                append_jsonl(
                    log_path,
                    {
                        "ts": time.time(),
                        "stage": "stage2_backtranslate",
                        "dataset": cfg.dataset,
                        "file": in_path.name,
                        "module": module_name,
                        "target_lang": tgt_lang,
                        "task": task,
                        "lang": lang,
                        "n_variants": n_variants,
                        "n_segments": len(prompts_en),
                        "bt_parallelism": bt_workers,
                        "elapsed_sec_stage2_total": float(elapsed_total),
                        "elapsed_sec_fw_api_sum": float(meta_fw.get("elapsed_sec", 0.0) or 0.0),
                        "elapsed_sec_bt_api_sum": float(meta_bt_sum.get("elapsed_sec", 0.0) or 0.0),
                        "prompt_tokens_fw": fw_pt,
                        "completion_tokens_fw": fw_ct,
                        "prompt_tokens_bt": bt_pt,
                        "completion_tokens_bt": bt_ct,
                        "prompt_tokens_total": fw_pt + bt_pt,
                        "completion_tokens_total": fw_ct + bt_ct,
                        "cost_usd": cost,
                    },
                )

            pbar_bt.close()

            tqdm.write(f"[DONE] stage1 saved: {s1_path}")
            tqdm.write(f"[DONE] stage2 meta saved: {meta_path}")
            tqdm.write(f"[DONE] final prompts saved: {out_path}")


def run_translate(cfg: TranslateConfig, env: Dict[str, str]) -> None:
    modules = [m.strip().lower() for m in cfg.modules if m.strip()]
    if not modules:
        raise ValueError("No translation modules configured")

    in_files = list_en_jsonl_files(cfg.prompts_dir)
    if not in_files:
        print(f"[WARN] No *en.jsonl files in: {cfg.prompts_dir}")
        return

    grand_total = 0
    for m in modules:
        n_variants = get_num_variants(m, env)
        for in_path in in_files:
            recs = read_jsonl(in_path)
            per_file_calls = len(recs) * n_variants * 2  # S1 + S2
            grand_total += per_file_calls * len(cfg.target_langs)

    all_position = len(modules) * 2
    all_pbar = tqdm(
        total=grand_total,
        desc="ALL",
        unit="call",
        dynamic_ncols=True,
        position=all_position,
        leave=True,
        bar_format="{desc}: {n_fmt}/{total_fmt} [{elapsed}<{remaining}, {rate_fmt}]",
    )
    all_lock = threading.Lock()

    max_workers = min(len(modules), int(env.get("MODULE_PARALLELISM", str(len(modules)))))

    with ThreadPoolExecutor(max_workers=max_workers) as ex:
        futs = []
        for idx, m in enumerate(modules):
            pos_base = idx * 2
            futs.append(
                ex.submit(
                    run_translate_for_module,
                    cfg,
                    env,
                    m,
                    pos_base=pos_base,
                    all_pbar=all_pbar,
                    all_lock=all_lock,
                )
            )
        for f in as_completed(futs):
            f.result()

    all_pbar.close()


# ─────────────────────────────────────────────────────────────
# Score (writes per-module scored jsonl)
# ─────────────────────────────────────────────────────────────


def _cometkiwi_means_for_variants(
    src_segments: List[str],
    mt_segments_by_variant: List[List[str]],
    model_name: Optional[str],
    batch_size: int,
) -> List[float]:
    """Efficient COMETKiwi scoring for N variants.

    Flatten all (variant, segment) pairs and run ONE model.predict() call,
    then compute per-variant mean. This is much faster than N separate predict() calls.
    """
    n_variants = len(mt_segments_by_variant)
    if not src_segments or n_variants == 0:
        return [0.0 for _ in range(n_variants)]

    n_segs = len(src_segments)
    for i in range(n_variants):
        if len(mt_segments_by_variant[i]) != n_segs:
            raise ValueError("src/mt segment length mismatch")

    if model_name is None:
        model_name = comet_default_model_name()

    model = cometkiwi_mod._load_comet_model(model_name)  # type: ignore[attr-defined]
    trainer = None
    try:
        trainer = cometkiwi_mod._get_or_create_trainer(batch_size=int(batch_size))  # type: ignore[attr-defined]
    except Exception:
        trainer = None

    data: List[Dict[str, str]] = []
    for i in range(n_variants):
        for s, t in zip(src_segments, mt_segments_by_variant[i]):
            data.append({"src": s or "", "mt": t or ""})

    pred_kwargs: Dict[str, Any] = {"batch_size": int(batch_size)}
    if trainer is None:
        pred_kwargs["gpus"] = 1 if getattr(cometkiwi_mod, "_has_cuda", lambda: False)() else 0  # type: ignore

    try:
        import inspect
        sig = inspect.signature(model.predict)
        if "trainer" in sig.parameters and trainer is not None:
            pred_kwargs["trainer"] = trainer
        if "progress_bar" in sig.parameters:
            pred_kwargs["progress_bar"] = False
        if "verbose" in sig.parameters:
            pred_kwargs["verbose"] = False
    except Exception:
        pass

    out = model.predict(data, **pred_kwargs)
    seg_scores = out.get("scores", [])
    if not isinstance(seg_scores, (list, tuple)) or len(seg_scores) != len(data):
        raise TypeError("[COMETKiwi] unexpected scores")

    scores: List[float] = []
    for i in range(n_variants):
        chunk = seg_scores[i * n_segs : (i + 1) * n_segs]
        scores.append(float(sum(float(x) for x in chunk) / max(1, len(chunk))))
    return scores

def run_calculate_score(cfg: ScoreConfig, env: Optional[Dict[str, str]] = None) -> None:
    """
    Reads stage2_meta and writes scored jsonl into cfg.final_dir/<tgt>/<module>/<file>.
    RESUME=1: if out file exists, skip tasks already present and append only remaining.
    """
    resume = _env_flag(env or {}, "RESUME", "0")

    # Global progress bar for ETA (across all langs/modules/files)
    total_recs = 0
    for _tgt in cfg.target_langs:
        for _mod in cfg.modules:
            _dir = cfg.translated_dir / "_stage2_meta" / _tgt / _mod
            if not _dir.exists():
                continue
            _files = sorted([p for p in _dir.iterdir() if p.is_file() and p.name.endswith("en.jsonl")])
            for _p in _files:
                try:
                    # fast line count (jsonl)
                    with _p.open("r", encoding="utf-8") as _f:
                        total_recs += sum(1 for _ in _f if _.strip())
                except Exception:
                    pass
    score_all_pbar = tqdm(
        total=total_recs,
        desc="SCORE_ALL",
        unit="prompt",
        dynamic_ncols=True,
        leave=True,
        bar_format="{desc}: {n_fmt}/{total_fmt} [{elapsed}<{remaining}, {rate_fmt}]",
    )

    for tgt_lang in cfg.target_langs:
        for module_name in cfg.modules:
            lang_dir = cfg.translated_dir / "_stage2_meta" / tgt_lang / module_name
            if not lang_dir.exists():
                continue

            in_files = sorted([p for p in lang_dir.iterdir() if p.is_file() and p.name.endswith("en.jsonl")])
            for in_path in in_files:
                recs = read_jsonl(in_path)

                out_path = cfg.final_dir / tgt_lang / module_name / in_path.name
                done_scored = _load_done_tasks(out_path) if resume else set()

                pending = [r for r in recs if (not resume) or (r.get("task") not in done_scored)]
                if not pending:
                    print(f"[SKIP] score already done: {out_path}")
                    continue

                out_recs: List[Dict[str, Any]] = []
                desc = f"score:{cfg.dataset}:{in_path.name} ({tgt_lang}/{module_name})"
                for rec in tqdm(pending, desc=desc, unit="prompt", dynamic_ncols=True, leave=False, bar_format="{desc}: {n_fmt}/{total_fmt} [{elapsed}<{remaining}, {rate_fmt}] | {postfix}"):
                    score_all_pbar.update(1)
                    prompts_en: List[str] = rec["prompts_en"]
                    n_variants = int(rec.get("n_variants", 0))

                    bert_vals: List[float] = []
                    comet_vals: List[float] = []
                    mixed_vals: List[float] = []

                    # COMETKiwi: batch across variants (one predict per task when possible)
                    mt_by_variant: List[List[str]] = [
                        rec[f"prompt_{j+1}_segments"] for j in range(n_variants)
                    ]
                    comet_vals = _cometkiwi_means_for_variants(
                        prompts_en, mt_by_variant, cfg.comet_model, batch_size=int((env or {}).get("COMET_BATCH_SIZE", "8"))
                    )

                    for i in range(n_variants):
                        bt_segs_en: List[str] = rec[f"prompt_{i+1}_bt_segments_en"]

                        b = bertscore_mean_f1(prompts_en, bt_segs_en) if prompts_en else 0.0
                        c = float(comet_vals[i]) if prompts_en else 0.0

                        bert_vals.append(b)
                        mixed_vals.append((b + c) / 2.0)

                    best_idx0 = max(range(n_variants), key=lambda k: mixed_vals[k]) if n_variants else 0
                    best_prompt = rec[f"prompt_{best_idx0+1}"] if n_variants else rec["prompt_en"]

                    out_recs.append(
                        {
                            "task": rec["task"],
                            "lang": rec["lang"],
                            "target_lang": tgt_lang,
                            "module": module_name,
                            "n_variants": n_variants,
                            "scores": {
                                "BERTScore_F1_mean": bert_vals,
                                "COMETKiwi_mean": comet_vals,
                                "mixed_mean": mixed_vals,
                            },
                            "best": {"idx": best_idx0 + 1, "prompt": best_prompt},
                        }
                    )

                _append_or_write_jsonl(out_path, out_recs, resume=resume)
                print(f"[DONE] score saved: {out_path} (+{len(out_recs)} recs)")


# ─────────────────────────────────────────────────────────────
# FINAL (best_overall only)
# ─────────────────────────────────────────────────────────────

    score_all_pbar.close()


def run_emit_final_prompts_global_best(
    score_dir: Path,
    out_dir: Path,
    tgt_langs: List[str],
    modules: List[str],
    env: Optional[Dict[str, str]] = None,
) -> None:
    """
    Global best final selection across ALL modules.

    For each (tgt_lang, file, task):
      - reads scored jsonl from score_dir/<tgt>/<module>/<file>
      - uses that module's best mixed score (best.idx + mixed_mean)
      - picks the SINGLE best prompt across modules
      - writes only best_overall:
          out_dir/<tgt_lang>/best_overall/<file>.jsonl

    Each output record:
      {task, lang, target_lang, prompt, module, best_mixed}

    RESUME=1 supported: skip tasks already present and append remaining.
    """
    resume = _env_flag(env or {}, "RESUME", "0")

    for tgt_lang in tgt_langs:
        file_names: set[str] = set()
        for m in modules:
            d = score_dir / tgt_lang / m
            if not d.exists():
                continue
            for p in d.iterdir():
                if p.is_file() and p.name.endswith("en.jsonl"):
                    file_names.add(p.name)

        for fname in sorted(file_names):
            out_path = out_dir / tgt_lang / "best_overall" / fname
            done_final = _load_done_tasks(out_path) if resume else set()

            best_by_task: Dict[str, Dict[str, Any]] = {}

            for m in modules:
                in_path = score_dir / tgt_lang / m / fname
                if not in_path.exists():
                    continue

                scored = read_jsonl(in_path)
                for r in scored:
                    task = r.get("task")
                    if not isinstance(task, str) or not task:
                        continue
                    if resume and task in done_final:
                        continue

                    scores = r.get("scores", {}) or {}
                    mixed = scores.get("mixed_mean", [])
                    best = r.get("best", {}) or {}
                    idx1 = int(best.get("idx", 1) or 1)
                    idx0 = max(0, idx1 - 1)

                    best_score = float("-inf")
                    if isinstance(mixed, list) and 0 <= idx0 < len(mixed):
                        try:
                            best_score = float(mixed[idx0])
                        except Exception:
                            best_score = float("-inf")

                    cand = {
                        "task": task,
                        "lang": r.get("lang"),
                        "target_lang": r.get("target_lang", tgt_lang),
                        "prompt": best.get("prompt"),
                        "module": m,
                        "best_mixed": best_score,
                    }

                    prev = best_by_task.get(task)
                    if prev is None or float(cand["best_mixed"]) > float(prev.get("best_mixed", float("-inf"))):
                        best_by_task[task] = cand

            if not best_by_task:
                print(f"[SKIP] best_overall already done or no scored files: {out_path}")
                continue

            out_recs: List[Dict[str, Any]] = []
            for task, cand in best_by_task.items():
                out_recs.append(
                    {
                        "task": task,
                        "lang": cand.get("lang"),
                        "target_lang": cand.get("target_lang"),
                        "prompt": cand.get("prompt"),
                        "module": cand.get("module"),
                        "best_mixed": cand.get("best_mixed"),
                    }
                )

            _append_or_write_jsonl(out_path, out_recs, resume=resume)
            print(f"[DONE] best_overall saved: {out_path} (+{len(out_recs)} recs)")


# ─────────────────────────────────────────────────────────────
# Env / CLI
# ─────────────────────────────────────────────────────────────

def env_required_dataset_dirs(env: Dict[str, str], dataset: str) -> Tuple[Path, Path, Path]:
    ds = dataset.upper()
    prompts_dir = Path(env[f"{ds}_PROMPTS_DIR"]).resolve()
    translated_dir = Path(env[f"{ds}_TRANSLATED_DIR"]).resolve()
    final_translated_dir = Path(env[f"{ds}_FINAL_TRANSLATED_DIR"]).resolve()
    return prompts_dir, translated_dir, final_translated_dir


def parse_list(env_val: str) -> List[str]:
    return [x.strip() for x in env_val.split(",") if x.strip()]


def choose_target_langs(env: Dict[str, str]) -> List[str]:
    from src.postprocess.preserve_code import LANG_MAP

    mode = env.get("TRANSLATE_MODE", "single").strip().lower()
    if mode == "all":
        langs = list(LANG_MAP.keys())
    elif mode == "single":
        langs = parse_list(env.get("TARGET_LANGUAGES", "ko"))
    else:
        raise ValueError(f"Unknown TRANSLATE_MODE: {mode}")

    langs = [x for x in langs if x != "en"]
    for x in langs:
        if x not in LANG_MAP:
            raise ValueError(f"Unknown target language code in selection: {x}")
    return langs


def parse_args() -> argparse.Namespace:
    p = argparse.ArgumentParser()
    p.add_argument("--mode", choices=["translate", "calculate_score", "get_final_prompt"], required=True)
    p.add_argument(
        "--translator",
        default="all",
        help="Translation module to run (e.g., 'openai', 'deepseek', 'nllb') or 'all' for .env TRANSLATION_MODULES",
    )
    return p.parse_args()


def main() -> None:
    load_dotenv()
    env = dict(os.environ)

    dataset = env["TARGET_DATASET"].strip()
    prompts_dir, translated_dir, final_translated_dir = env_required_dataset_dirs(env, dataset)

    target_langs = choose_target_langs(env)
    env_modules = parse_list(env.get("TRANSLATION_MODULES", "openai"))

    base_prompt_path = Path(env.get("PROMPT_BASE_PATH", "src/prompts/translation/base.txt")).resolve()
    if not base_prompt_path.exists():
        raise FileNotFoundError(f"base prompt template not found: {base_prompt_path}")

    temperature = float(env.get("TEMPERATURE", "0.0"))

    args = parse_args()
    modules = env_modules if args.translator.strip().lower() == "all" else [args.translator.strip().lower()]

    if args.mode == "translate":
        run_translate(
            TranslateConfig(
                dataset=dataset,
                prompts_dir=prompts_dir,
                translated_dir=translated_dir,
                modules=env_modules,
                target_langs=target_langs,
                base_prompt_path=base_prompt_path,
                temperature=temperature,
            ),
            env=env,
        )

    elif args.mode == "calculate_score":
        run_calculate_score(
            ScoreConfig(
                dataset=dataset,
                translated_dir=translated_dir,
                final_dir=final_translated_dir,
                modules=modules,
                target_langs=target_langs,
                comet_model=env.get("COMET_MODEL_NAME", comet_default_model_name()),
            ),
            env=env,
        )
        run_emit_final_prompts_global_best(
            score_dir=final_translated_dir,
            out_dir=final_translated_dir / "final_prompts",
            tgt_langs=target_langs,
            modules=modules,
            env=env,
        )

    elif args.mode == "get_final_prompt":
        run_translate(
            TranslateConfig(
                dataset=dataset,
                prompts_dir=prompts_dir,
                translated_dir=translated_dir,
                modules=modules,
                target_langs=target_langs,
                base_prompt_path=base_prompt_path,
                temperature=temperature,
            ),
            env=env,
        )
        run_calculate_score(
            ScoreConfig(
                dataset=dataset,
                translated_dir=translated_dir,
                final_dir=final_translated_dir,
                modules=modules,
                target_langs=target_langs,
                comet_model=env.get("COMET_MODEL_NAME", comet_default_model_name()),
            ),
            env=env,
        )
        run_emit_final_prompts_global_best(
            score_dir=final_translated_dir,
            out_dir=final_translated_dir / "final_prompts",
            tgt_langs=target_langs,
            modules=modules,
            env=env,
        )
    else:
        raise ValueError(f"Unknown mode: {args.mode}")


if __name__ == "__main__":
    main()
