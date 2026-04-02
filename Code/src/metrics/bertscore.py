# -*- coding: utf-8 -*-
from __future__ import annotations

import gc
import os
import warnings
import logging
from typing import Any, List, Optional, Tuple

if "HF_HOME" in os.environ:
    os.environ["HF_HOME"] = os.environ["HF_HOME"]
if "TORCH_HOME" in os.environ:
    os.environ["TORCH_HOME"] = os.environ["TORCH_HOME"]

os.environ.setdefault("TOKENIZERS_PARALLELISM", "false")
os.environ.setdefault("TRANSFORMERS_VERBOSITY", "error")
os.environ.setdefault("PYTHONWARNINGS", "ignore")
warnings.filterwarnings("ignore")
for name in ["transformers", "huggingface_hub"]:
    logging.getLogger(name).setLevel(logging.ERROR)

try:
    import torch
except Exception:
    torch = None  # type: ignore

try:
    from bert_score import BERTScorer
except Exception:
    BERTScorer = None  # type: ignore


_BERT_SCORER: Any = None
_BERT_SCORER_CFG: Tuple[str, str, str] = ("", "", "")

_DEFAULT_MODEL = os.environ.get("BERTSCORE_MODEL", "xlm-roberta-large")
_DEFAULT_LANG = os.environ.get("BERTSCORE_LANG", "en")


def _has_cuda() -> bool:
    return bool(torch is not None and hasattr(torch, "cuda") and torch.cuda.is_available())


def _resolve_device() -> str:
    device = (os.environ.get("BERTSCORE_DEVICE") or "").strip()
    if device:
        return device

    gpu = (os.environ.get("BERTSCORE_CUDA_VISIBLE_DEVICES") or os.environ.get("BERTSCORE_GPU") or "").strip()
    if gpu and _has_cuda():
        first = gpu.split(",")[0].strip()
        if first.isdigit():
            return f"cuda:{first}"
        return "cuda"

    return "cuda" if _has_cuda() else "cpu"


def _get_scorer(model_type: str, lang: str) -> Any:
    global _BERT_SCORER, _BERT_SCORER_CFG

    if BERTScorer is None:
        raise ImportError("bert-score is not installed. Install: pip install bert-score sentencepiece")

    device = _resolve_device()
    cfg = (model_type, lang, device)
    if _BERT_SCORER is not None and _BERT_SCORER_CFG == cfg:
        return _BERT_SCORER

    kwargs = dict(
        model_type=model_type,
        lang=lang,
        device=device,
        rescale_with_baseline=False,
    )

    try:
        _BERT_SCORER = BERTScorer(**kwargs, verbose=False)
    except TypeError:
        _BERT_SCORER = BERTScorer(**kwargs)

    _BERT_SCORER_CFG = cfg
    return _BERT_SCORER


def bertscore_mean_f1(
    refs: List[str],
    cands: List[str],
    model_type: Optional[str] = None,
    lang: Optional[str] = None,
) -> float:
    if len(refs) != len(cands):
        raise ValueError("refs and cands length mismatch")
    if not refs:
        return 0.0

    model_type = model_type or _DEFAULT_MODEL
    lang = lang or _DEFAULT_LANG
    scorer = _get_scorer(model_type=model_type, lang=lang)

    _, _, f1 = scorer.score(cands, refs)
    return float(f1.mean().item())


def bertscore_means_for_variants(
    refs: List[str],
    cands_by_variant: List[List[str]],
    model_type: Optional[str] = None,
    lang: Optional[str] = None,
) -> List[float]:
    if not refs or not cands_by_variant:
        return [0.0 for _ in cands_by_variant]

    n_variants = len(cands_by_variant)
    n_segs = len(refs)
    for cands in cands_by_variant:
        if len(cands) != n_segs:
            raise ValueError("refs and cands length mismatch")

    model_type = model_type or _DEFAULT_MODEL
    lang = lang or _DEFAULT_LANG
    scorer = _get_scorer(model_type=model_type, lang=lang)

    flat_refs: List[str] = []
    flat_cands: List[str] = []
    for cands in cands_by_variant:
        flat_refs.extend(refs)
        flat_cands.extend(cands)

    _, _, f1 = scorer.score(flat_cands, flat_refs)
    vals = [float(x) for x in f1.tolist()]

    out: List[float] = []
    for i in range(n_variants):
        chunk = vals[i * n_segs : (i + 1) * n_segs]
        out.append(float(sum(chunk) / max(1, len(chunk))))
    return out


def bertscore_release() -> None:
    global _BERT_SCORER, _BERT_SCORER_CFG
    _BERT_SCORER = None
    _BERT_SCORER_CFG = ("", "", "")
    gc.collect()
    if torch is not None and hasattr(torch, "cuda") and torch.cuda.is_available():
        try:
            torch.cuda.empty_cache()
        except Exception:
            pass
