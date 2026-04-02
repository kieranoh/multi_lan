# -*- coding: utf-8 -*-
from __future__ import annotations

import gc
import os
import time
import warnings
import logging
import inspect
from typing import Any, Dict, List, Optional, Tuple

if "HF_HOME" in os.environ:
    os.environ["HF_HOME"] = os.environ["HF_HOME"]
if "TORCH_HOME" in os.environ:
    os.environ["TORCH_HOME"] = os.environ["TORCH_HOME"]

os.environ.setdefault("TOKENIZERS_PARALLELISM", "false")
os.environ.setdefault("TRANSFORMERS_VERBOSITY", "error")
os.environ.setdefault("PYTHONWARNINGS", "ignore")
warnings.filterwarnings("ignore")
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
_COMET_MODEL_CFG: Tuple[str, str] = ("", "")
_COMET_TRAINER: Any = None
_COMET_TRAINER_CFG: Tuple[str, int] = ("", 0)

_COMET_MODEL_NAME_DEFAULT = "Unbabel/wmt22-cometkiwi-da"


def comet_default_model_name() -> str:
    return _COMET_MODEL_NAME_DEFAULT


def _has_cuda() -> bool:
    return bool(torch is not None and hasattr(torch, "cuda") and torch.cuda.is_available())


def _resolve_device() -> str:
    device = (os.environ.get("COMET_DEVICE") or "").strip()
    if device:
        return device

    gpu = (os.environ.get("COMET_CUDA_VISIBLE_DEVICES") or os.environ.get("COMET_GPU") or "").strip()
    if gpu and _has_cuda():
        first = gpu.split(",")[0].strip()
        if first.isdigit():
            return f"cuda:{first}"
        return "cuda"

    return "cuda" if _has_cuda() else "cpu"


def _trainer_devices(device: str):
    if not device.startswith("cuda"):
        return ("cpu", 1)
    if ":" in device:
        try:
            idx = int(device.split(":", 1)[1])
            return ("gpu", [idx])
        except Exception:
            return ("gpu", 1)
    return ("gpu", 1)


def _load_comet_model(model_name: str) -> Any:
    global _COMET_MODEL, _COMET_MODEL_CFG

    device = _resolve_device()
    cfg = (model_name, device)
    if _COMET_MODEL is not None and _COMET_MODEL_CFG == cfg:
        return _COMET_MODEL

    if download_model is None or load_from_checkpoint is None:
        raise ImportError('unbabel-comet is not installed. Install: pip install "unbabel-comet>=2.0.0"')

    path = download_model(model_name)
    model = load_from_checkpoint(path)
    try:
        model.to(device)
    except Exception:
        pass
    _COMET_MODEL = model
    _COMET_MODEL_CFG = cfg
    return _COMET_MODEL


def _get_or_create_trainer(batch_size: int) -> Any:
    global _COMET_TRAINER, _COMET_TRAINER_CFG

    if Trainer is None:
        return None

    device = _resolve_device()
    cfg = (device, int(batch_size))
    if _COMET_TRAINER is not None and _COMET_TRAINER_CFG == cfg:
        return _COMET_TRAINER

    accelerator, devices = _trainer_devices(device)
    kwargs: Dict[str, Any] = dict(
        logger=False,
        enable_checkpointing=False,
        enable_progress_bar=False,
    )

    try:
        kwargs.update({"accelerator": accelerator, "devices": devices})
        _COMET_TRAINER = Trainer(**kwargs)
    except TypeError:
        kwargs.pop("accelerator", None)
        kwargs.pop("devices", None)
        if accelerator == "gpu":
            kwargs["gpus"] = devices
        _COMET_TRAINER = Trainer(**kwargs)

    _COMET_TRAINER_CFG = cfg
    return _COMET_TRAINER


def cometkiwi_mean(
    src_segments: List[str],
    mt_segments: List[str],
    model_name: Optional[str] = None,
    batch_size: int = 8,
) -> float:
    s, _ = cometkiwi_mean_with_meta(src_segments, mt_segments, model_name=model_name, batch_size=batch_size)
    return s


def cometkiwi_mean_with_meta(
    src_segments: List[str],
    mt_segments: List[str],
    model_name: Optional[str] = None,
    batch_size: int = 8,
) -> Tuple[float, Dict[str, Any]]:
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

    try:
        sig = inspect.signature(model.predict)
        if "trainer" in sig.parameters and trainer is not None:
            pred_kwargs["trainer"] = trainer
        if "progress_bar" in sig.parameters:
            pred_kwargs["progress_bar"] = False
        if "verbose" in sig.parameters:
            pred_kwargs["verbose"] = False
        if "gpus" in sig.parameters and ("trainer" not in pred_kwargs):
            pred_kwargs["gpus"] = 1 if _resolve_device().startswith("cuda") else 0
    except Exception:
        if trainer is None:
            pred_kwargs["gpus"] = 1 if _resolve_device().startswith("cuda") else 0

    out = model.predict(data, **pred_kwargs)
    dt = float(time.perf_counter() - t0)

    seg_scores = out.get("scores", [])
    if not isinstance(seg_scores, (list, tuple)) or len(seg_scores) != len(data):
        raise TypeError(f"[COMETKiwi] unexpected scores: {type(seg_scores)}")

    mean_score = float(sum(float(x) for x in seg_scores) / len(seg_scores))
    used_gpu = bool(_resolve_device().startswith("cuda"))

    return mean_score, {
        "elapsed_sec": dt,
        "used_gpu": used_gpu,
        "batch_size": int(batch_size),
        "n_items": len(data),
        "model": model_name,
        "device": _resolve_device(),
    }


def cometkiwi_means_for_variants(
    src_segments: List[str],
    mt_segments_by_variant: List[List[str]],
    model_name: Optional[str] = None,
    batch_size: int = 8,
) -> List[float]:
    n_variants = len(mt_segments_by_variant)
    if not src_segments or n_variants == 0:
        return [0.0 for _ in range(n_variants)]

    n_segs = len(src_segments)
    for i in range(n_variants):
        if len(mt_segments_by_variant[i]) != n_segs:
            raise ValueError("src/mt segment length mismatch")

    if model_name is None:
        model_name = _COMET_MODEL_NAME_DEFAULT

    model = _load_comet_model(model_name)
    trainer = _get_or_create_trainer(batch_size=int(batch_size))

    data: List[Dict[str, str]] = []
    for i in range(n_variants):
        for s, t in zip(src_segments, mt_segments_by_variant[i]):
            data.append({"src": s or "", "mt": t or ""})

    pred_kwargs: Dict[str, Any] = {"batch_size": int(batch_size)}
    try:
        sig = inspect.signature(model.predict)
        if "trainer" in sig.parameters and trainer is not None:
            pred_kwargs["trainer"] = trainer
        if "progress_bar" in sig.parameters:
            pred_kwargs["progress_bar"] = False
        if "verbose" in sig.parameters:
            pred_kwargs["verbose"] = False
        if "gpus" in sig.parameters and ("trainer" not in pred_kwargs):
            pred_kwargs["gpus"] = 1 if _resolve_device().startswith("cuda") else 0
    except Exception:
        if trainer is None:
            pred_kwargs["gpus"] = 1 if _resolve_device().startswith("cuda") else 0

    out = model.predict(data, **pred_kwargs)
    seg_scores = out.get("scores", [])
    if not isinstance(seg_scores, (list, tuple)) or len(seg_scores) != len(data):
        raise TypeError("[COMETKiwi] unexpected scores")

    scores: List[float] = []
    for i in range(n_variants):
        chunk = seg_scores[i * n_segs : (i + 1) * n_segs]
        scores.append(float(sum(float(x) for x in chunk) / max(1, len(chunk))))
    return scores


def cometkiwi_release() -> None:
    global _COMET_MODEL, _COMET_MODEL_CFG, _COMET_TRAINER, _COMET_TRAINER_CFG
    _COMET_MODEL = None
    _COMET_MODEL_CFG = ("", "")
    _COMET_TRAINER = None
    _COMET_TRAINER_CFG = ("", 0)
    gc.collect()
    if torch is not None and hasattr(torch, "cuda") and torch.cuda.is_available():
        try:
            torch.cuda.empty_cache()
        except Exception:
            pass
