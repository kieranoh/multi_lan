# -*- coding: utf-8 -*-
from __future__ import annotations

import json
import os
import time
import random
import threading
from dataclasses import dataclass
from datetime import datetime, timezone
from pathlib import Path
from typing import Any, Dict, List, Tuple, Optional

from src.translators.openai import OpenAITranslator


def _utc_now_iso() -> str:
    return datetime.now(timezone.utc).isoformat()


def _safe_mkdir(p: Path) -> None:
    p.mkdir(parents=True, exist_ok=True)


def _append_jsonl(path: Path, obj: Dict[str, Any], lock: threading.Lock) -> None:
    _safe_mkdir(path.parent)
    line = json.dumps(obj, ensure_ascii=False)
    with lock:
        with path.open("a", encoding="utf-8") as f:
            f.write(line + "\n")


def _summarize_messages(messages: List[Dict[str, str]], max_chars: int = 2000) -> Dict[str, Any]:
    total_chars = 0
    parts = []
    for m in messages:
        role = m.get("role", "")
        content = m.get("content", "")
        total_chars += len(content)
        parts.append(
            {
                "role": role,
                "content_chars": len(content),
                "content_head": content[:max_chars],
            }
        )
    return {"total_chars": total_chars, "messages": parts}


@dataclass
class TraceOpenAITranslator(OpenAITranslator):
    """
    OpenAITranslator와 동일하게 동작하되,
    요청(messages)과 응답(raw content), 예외를 JSONL로 모두 기록합니다.
    """

    trace_path: Optional[Path] = None
    trace_lock: Optional[threading.Lock] = None

    full_messages: bool = True
    max_head_chars: int = 4000
    run_tag: str = "trace"

    # translate_prompt_variants에서 채워서 _attempt_call 로그에 포함
    _trace_ctx: Dict[str, Any] = None  # type: ignore

    def _write(self, rec: Dict[str, Any]) -> None:
        if self.trace_path is None or self.trace_lock is None:
            return
        _append_jsonl(self.trace_path, rec, self.trace_lock)

    def translate_prompt_variants(
        self,
        segments: List[str],
        src_lang: str,
        tgt_lang: str,
        n_variants: int,
        temperature: float,
    ) -> Tuple[List[List[str]], Dict[str, Any]]:
        # ✅ 호출 컨텍스트 기록(파일/태스크명까지는 translate.py가 안 넘겨주므로 여기까지가 최대)
        seg_chars = sum(len(s) for s in (segments or []))
        self._trace_ctx = {
            "src_lang": src_lang,
            "tgt_lang": tgt_lang,
            "n_variants": int(n_variants),
            "n_segments": int(len(segments or [])),
            "segments_total_chars": int(seg_chars),
        }
        return super().translate_prompt_variants(
            segments=segments,
            src_lang=src_lang,
            tgt_lang=tgt_lang,
            n_variants=n_variants,
            temperature=temperature,
        )

    def _attempt_call(self, client, messages, temperature: float) -> Tuple[str, int, int, float]:
        req_id = f"{self.run_tag}-{int(time.time() * 1000)}-{threading.get_ident()}"
        t0 = time.perf_counter()

        ctx = self._trace_ctx or {}

        req_log: Dict[str, Any] = {
            "ts_utc": _utc_now_iso(),
            "event": "request",
            "req_id": req_id,
            "module": getattr(self, "name", "openai"),
            "model": getattr(self, "model", None),
            "base_url": getattr(self, "base_url", None),
            "temperature": float(temperature),
            **ctx,
        }

        if self.full_messages:
            req_log["messages"] = messages
        else:
            req_log["messages_summary"] = _summarize_messages(messages, max_chars=self.max_head_chars)

        self._write(req_log)

        try:
            content, pt, ct, dt = super()._attempt_call(client, messages, temperature=temperature)

            resp_log: Dict[str, Any] = {
                "ts_utc": _utc_now_iso(),
                "event": "response",
                "req_id": req_id,
                "elapsed_sec": float(dt),
                "prompt_tokens": int(pt),
                "completion_tokens": int(ct),
                "content": content,
                "content_chars": len(content or ""),
            }
            self._write(resp_log)
            return content, pt, ct, dt

        except Exception as e:
            dt = time.perf_counter() - t0
            err_log: Dict[str, Any] = {
                "ts_utc": _utc_now_iso(),
                "event": "error",
                "req_id": req_id,
                "elapsed_sec": float(dt),
                "error_type": type(e).__name__,
                "error_str": str(e),
            }
            self._write(err_log)
            raise


@dataclass
class TraceDeepSeekTranslator(TraceOpenAITranslator):
    """
    deepseek는 OpenAITranslator 기반 구현을 그대로 쓰는 구조라,
    base_url/model/api_key만 deepseek로 맞춰주면 동일하게 트레이싱 가능합니다.
    """

    @classmethod
    def from_env(cls, env: Dict[str, str], system_template: str) -> "TraceDeepSeekTranslator":
        api_key = env["DEEPSEEK_API_KEY"]
        base_url = env.get("DEEPSEEK_BASE_URL", "https://api.deepseek.com")
        model = env.get("DEEPSEEK_MODEL_NAME", "deepseek-chat")
        return cls(
            name="deepseek",
            model=model,
            api_key=api_key,
            system_template=system_template,
            base_url=base_url,
        )
