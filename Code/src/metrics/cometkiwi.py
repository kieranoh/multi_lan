# -*- coding: utf-8 -*-
from __future__ import annotations
import os
if "HF_HOME" in os.environ:
    os.environ["HF_HOME"] = os.environ["HF_HOME"]

if "TORCH_HOME" in os.environ:
    os.environ["TORCH_HOME"] = os.environ["TORCH_HOME"]


from typing import Any, List

try:
    from comet import download_model, load_from_checkpoint
except Exception:
    download_model = None  # type: ignore
    load_from_checkpoint = None  # type: ignore

try:
    import torch
except Exception:
    torch = None  # type: ignore


_COMET_MODEL = None
_COMET_MODEL_NAME_DEFAULT = "Unbabel/wmt22-cometkiwi-da"


def comet_default_model_name() -> str:
    return _COMET_MODEL_NAME_DEFAULT


def _load_comet_model(model_name: str) -> Any:
    global _COMET_MODEL
    if _COMET_MODEL is not None:
        return _COMET_MODEL

    if download_model is None or load_from_checkpoint is None:
        raise ImportError('unbabel-comet is not installed. Install: pip install "unbabel-comet>=2.0.0"')

    path = download_model(model_name)
    _COMET_MODEL = load_from_checkpoint(path)
    return _COMET_MODEL


def cometkiwi_mean(src_segments: List[str], mt_segments: List[str], model_name: str | None = None) -> float:
    """
    src_segments: 원본(en) 세그먼트 리스트
    mt_segments : 번역(mt) 세그먼트 리스트 (예: forward 번역 세그먼트)
    """
    if len(src_segments) != len(mt_segments):
        raise ValueError("src_segments and mt_segments length mismatch")
    if not src_segments:
        return 0.0

    if model_name is None:
        model_name = _COMET_MODEL_NAME_DEFAULT

    model = _load_comet_model(model_name)
    data = [{"src": s, "mt": t} for s, t in zip(src_segments, mt_segments)]

    gpus = 0
    if torch is not None and hasattr(torch, "cuda") and torch.cuda.is_available():
        gpus = 1

    out = model.predict(data, batch_size=8, gpus=gpus)
    seg_scores = out.get("scores", [])
    if not isinstance(seg_scores, (list, tuple)) or len(seg_scores) != len(data):
        raise TypeError(f"[COMETKiwi] unexpected scores: {type(seg_scores)}")

    return float(sum(float(x) for x in seg_scores) / len(seg_scores))
