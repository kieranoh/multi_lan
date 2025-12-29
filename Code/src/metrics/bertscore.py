# -*- coding: utf-8 -*-
from __future__ import annotations

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


def _get_scorer(model_type: str, lang: str) -> Any:
    """
    Cache BERTScorer instance (loads tokenizer/model once).
    Compatible with older bert-score versions that don't accept verbose=.
    """
    global _BERT_SCORER, _BERT_SCORER_CFG

    if BERTScorer is None:
        raise ImportError("bert-score is not installed. Install: pip install bert-score sentencepiece")

    device = "cuda" if _has_cuda() else "cpu"
    cfg = (model_type, lang, device)
    if _BERT_SCORER is not None and _BERT_SCORER_CFG == cfg:
        return _BERT_SCORER

    kwargs = dict(
        model_type=model_type,
        lang=lang,
        device=device,
        rescale_with_baseline=False,
    )

    # Some versions accept verbose, some don't
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
    """
    Mean F1 for aligned lists (refs[i] vs cands[i]).
    Uses cached scorer; GPU if available.
    """
    if len(refs) != len(cands):
        raise ValueError("refs and cands length mismatch")
    if not refs:
        return 0.0

    model_type = model_type or _DEFAULT_MODEL
    lang = lang or _DEFAULT_LANG
    scorer = _get_scorer(model_type=model_type, lang=lang)

    P, R, F1 = scorer.score(cands, refs)
    return float(F1.mean().item())
