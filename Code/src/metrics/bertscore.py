# -*- coding: utf-8 -*-
from __future__ import annotations
import os
if "HF_HOME" in os.environ:
    os.environ["HF_HOME"] = os.environ["HF_HOME"]

if "TORCH_HOME" in os.environ:
    os.environ["TORCH_HOME"] = os.environ["TORCH_HOME"]



from typing import List
from bert_score import score as bertscore_score

_BERT_MODEL = "xlm-roberta-base"
_BERT_LANG = "en"


def bertscore_mean_f1(ref_segments: List[str], cand_segments: List[str]) -> float:
    """
    ref_segments: 원본(en) 세그먼트 리스트
    cand_segments: 비교 대상 세그먼트 리스트 (예: back-translation 결과)
    """
    if len(ref_segments) != len(cand_segments):
        raise ValueError("ref_segments and cand_segments length mismatch")
    if not ref_segments:
        return 0.0

    refs = [r if r.strip() else "EMPTY" for r in ref_segments]
    cands = [c if c.strip() else "EMPTY" for c in cand_segments]

    _, _, F1 = bertscore_score(
        cands,
        refs,
        model_type=_BERT_MODEL,
        lang=_BERT_LANG,
        verbose=False,
    )
    vals = [float(x.item()) for x in F1]
    return float(sum(vals) / len(vals))
