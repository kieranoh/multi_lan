# -*- coding: utf-8 -*-
from __future__ import annotations

import os
import time
import warnings
import logging
import inspect
from typing import Any, Dict, List, Optional, Tuple

# ---- env passthrough (your style) ----
if "HF_HOME" in os.environ:
    os.environ["HF_HOME"] = os.environ["HF_HOME"]
if "TORCH_HOME" in os.environ:
    os.environ["TORCH_HOME"] = os.environ["TORCH_HOME"]

# ---- reduce spam ----
os.environ.setdefault("TOKENIZERS_PARALLELISM", "false")
os.environ.setdefault("TRANSFORMERS_VERBOSITY", "error")
os.environ.setdefault("PYTHONWARNINGS", "ignore")
warnings.filterwarnings("ignore")

# lightning / transformers log level
for name in ["pytorch_lightning", "lightning", "transformers", "huggingface_hub"]:
    logging.getLogger(name).setLevel(logging.ERROR)

try:
    from comet import download_model, load_from_checkpoint
except Exception:
    download_model = None  # type: ignore
    load_from_checkpoint = None  # type: ignore

try:
    import torch
except Exception:
    torch = None  # type: ignore

try:
    from pytorch_lightning import Trainer
except Exception:
    Trainer = None  # type: ignore


_COMET_MODEL: Any = None
_COMET_TRAINER: Any = None
_COMET_TRAINER_CFG: Tuple[bool, int] = (False, 0)

_COMET_MODEL_NAME_DEFAULT = "Unbabel/wmt22-cometkiwi-da"


def comet_default_model_name() -> str:
    return _COMET_MODEL_NAME_DEFAULT


def _has_cuda() -> bool:
    return bool(torch is not None and hasattr(torch, "cuda") and torch.cuda.is_available())


def _load_comet_model(model_name: str) -> Any:
    global _COMET_MODEL
    if _COMET_MODEL is not None:
        return _COMET_MODEL

    if download_model is None or load_from_checkpoint is None:
        raise ImportError('unbabel-comet is not installed. Install: pip install "unbabel-comet>=2.0.0"')

    path = download_model(model_name)
    _COMET_MODEL = load_from_checkpoint(path)
    return _COMET_MODEL


def _get_or_create_trainer(batch_size: int) -> Any:
    """
    Create one Lightning Trainer and reuse it.
    Force GPU usage when CUDA is available.
    """
    global _COMET_TRAINER, _COMET_TRAINER_CFG

    if Trainer is None:
        return None

    use_gpu = _has_cuda()
    cfg = (use_gpu, int(batch_size))
    if _COMET_TRAINER is not None and _COMET_TRAINER_CFG == cfg:
        return _COMET_TRAINER

    kwargs: Dict[str, Any] = dict(
        logger=False,
        enable_checkpointing=False,
        enable_progress_bar=False,
    )

    # PL 2.x preferred
    try:
        if use_gpu:
            kwargs.update({"accelerator": "gpu", "devices": 1})
        else:
            kwargs.update({"accelerator": "cpu", "devices": 1})
        _COMET_TRAINER = Trainer(**kwargs)
    except TypeError:
        # fallback for older PL
        kwargs.pop("accelerator", None)
        kwargs.pop("devices", None)
        if use_gpu:
            kwargs["gpus"] = 1
        _COMET_TRAINER = Trainer(**kwargs)

    _COMET_TRAINER_CFG = cfg
    return _COMET_TRAINER


def cometkiwi_mean(
    src_segments: List[str],
    mt_segments: List[str],
    model_name: Optional[str] = None,
    batch_size: int = 8,
) -> float:
    """
    Backward-compatible API: returns mean score only.
    (Time/metadata is available via cometkiwi_mean_with_meta)
    """
    s, _ = cometkiwi_mean_with_meta(src_segments, mt_segments, model_name=model_name, batch_size=batch_size)
    return s


def cometkiwi_mean_with_meta(
    src_segments: List[str],
    mt_segments: List[str],
    model_name: Optional[str] = None,
    batch_size: int = 8,
) -> Tuple[float, Dict[str, Any]]:
    """
    Returns (mean_score, meta) where meta includes elapsed_sec and whether GPU was used.
    """
    if len(src_segments) != len(mt_segments):
        raise ValueError("src_segments and mt_segments length mismatch")
    if not src_segments:
        return 0.0, {"elapsed_sec": 0.0, "used_gpu": False}

    if model_name is None:
        model_name = _COMET_MODEL_NAME_DEFAULT

    model = _load_comet_model(model_name)
    data = [{"src": s or "", "mt": t or ""} for s, t in zip(src_segments, mt_segments)]

    trainer = _get_or_create_trainer(batch_size=int(batch_size))
    t0 = time.perf_counter()

    pred_kwargs: Dict[str, Any] = {"batch_size": int(batch_size)}

    # Some COMET versions accept trainer=, some don't. Detect.
    try:
        sig = inspect.signature(model.predict)
        if "trainer" in sig.parameters and trainer is not None:
            pred_kwargs["trainer"] = trainer
        # quiet flags
        if "progress_bar" in sig.parameters:
            pred_kwargs["progress_bar"] = False
        if "verbose" in sig.parameters:
            pred_kwargs["verbose"] = False
        # legacy gpus arg sometimes exists; avoid it if trainer exists
        if "gpus" in sig.parameters and ("trainer" not in pred_kwargs):
            pred_kwargs["gpus"] = 1 if _has_cuda() else 0
    except Exception:
        # minimal fallback
        if trainer is None:
            pred_kwargs["gpus"] = 1 if _has_cuda() else 0

    out = model.predict(data, **pred_kwargs)
    dt = float(time.perf_counter() - t0)

    seg_scores = out.get("scores", [])
    if not isinstance(seg_scores, (list, tuple)) or len(seg_scores) != len(data):
        raise TypeError(f"[COMETKiwi] unexpected scores: {type(seg_scores)}")

    mean_score = float(sum(float(x) for x in seg_scores) / len(seg_scores))
    used_gpu = bool(_has_cuda() and (trainer is not None or pred_kwargs.get("gpus", 0) == 1))

    return mean_score, {
        "elapsed_sec": dt,
        "used_gpu": used_gpu,
        "batch_size": int(batch_size),
        "n_items": len(data),
        "model": model_name,
    }
