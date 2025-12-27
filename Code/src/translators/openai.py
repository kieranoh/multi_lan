# -*- coding: utf-8 -*-
from __future__ import annotations

import html as _html
import os
import time
from concurrent.futures import ThreadPoolExecutor, as_completed
from dataclasses import dataclass
from typing import Any, Dict, List, Tuple, Optional

from src.postprocess.preserve_code import (
    LANG_MAP,
    pack_segments_with_labels,
    safe_json_loads,
    unpack_labeled_json,
)

try:
    from openai import OpenAI
except Exception:
    OpenAI = None  # type: ignore


@dataclass
class OpenAITranslator:
    name: str
    model: str
    api_key: str
    system_template: str
    base_url: Optional[str] = None
    request_timeout_s: Optional[float] = None

    @classmethod
    def from_env(cls, env: Dict[str, str], system_template: str) -> "OpenAITranslator":
        api_key = env["OPENAI_API_KEY"]
        model = env.get("OPENAI_MODEL_NAME", env.get("MODEL_NAME", "gpt-4o-mini"))
        base_url = env.get("OPENAI_BASE_URL")
        return cls(
            name="openai",
            model=model,
            api_key=api_key,
            system_template=system_template,
            base_url=base_url,
        )

    def _client(self):
        if OpenAI is None:
            raise ImportError("openai package is not available.")
        return OpenAI(api_key=self.api_key, base_url=self.base_url) if self.base_url else OpenAI(api_key=self.api_key)

    def _system_msg(self, src_lang: str, tgt_lang: str, n_variants: int) -> str:
        if src_lang not in LANG_MAP or tgt_lang not in LANG_MAP:
            raise ValueError(f"Unknown language code: {src_lang}->{tgt_lang}")
        msg = (
            self.system_template
            .replace("{{SRC_LABEL}}", LANG_MAP[src_lang])
            .replace("{{TARGET_LABEL}}", LANG_MAP[tgt_lang])
        )
        msg = msg.replace("{{N_VARIANTS}}", str(n_variants))
        return msg

    def translate_prompt_variants(
        self,
        segments: List[str],
        src_lang: str,
        tgt_lang: str,
        n_variants: int,
        temperature: float,
    ) -> Tuple[List[List[str]], Dict[str, Any]]:
        if not segments:
            return ([[] for _ in range(n_variants)], {"prompt_tokens": 0, "completion_tokens": 0, "elapsed_sec": 0.0})

        client = self._client()
        system_msg = self._system_msg(src_lang, tgt_lang, n_variants)

        packed = pack_segments_with_labels(segments)
        messages = [
            {"role": "system", "content": system_msg},
            {"role": "user", "content": packed},
        ]

        try:
            variant_workers = max(1, int(os.environ.get("VARIANT_PARALLELISM", "1")))
        except Exception:
            variant_workers = 1
        variant_workers = min(variant_workers, n_variants)

        def one_call() -> Tuple[List[str], int, int, float]:
            t0 = time.perf_counter()
            resp = client.chat.completions.create(
                model=self.model,
                messages=messages,
                temperature=float(temperature),
            )
            dt = time.perf_counter() - t0

            content = resp.choices[0].message.content
            obj = safe_json_loads(content)
            data = unpack_labeled_json(obj, n_segments=len(segments))

            prompt_tokens = 0
            completion_tokens = 0
            try:
                usage = getattr(resp, "usage", None)
                if usage is not None:
                    prompt_tokens = int(getattr(usage, "prompt_tokens", 0) or 0)
                    completion_tokens = int(getattr(usage, "completion_tokens", 0) or 0)
            except Exception:
                pass

            cleaned = [_html.unescape(x).strip() for x in data]
            return cleaned, prompt_tokens, completion_tokens, float(dt)

        variants: List[List[str]] = [[] for _ in range(n_variants)]
        prompt_tokens_sum = 0
        completion_tokens_sum = 0
        elapsed_sum = 0.0

        if variant_workers > 1 and n_variants > 1:
            with ThreadPoolExecutor(max_workers=variant_workers) as ex:
                futs = [ex.submit(one_call) for _ in range(n_variants)]
                for i, fut in enumerate(as_completed(futs)):
                    data, pt, ct, dt = fut.result()
                    variants[i] = data
                    prompt_tokens_sum += pt
                    completion_tokens_sum += ct
                    elapsed_sum += dt
        else:
            for i in range(n_variants):
                data, pt, ct, dt = one_call()
                variants[i] = data
                prompt_tokens_sum += pt
                completion_tokens_sum += ct
                elapsed_sum += dt

        meta = {
            "prompt_tokens": int(prompt_tokens_sum),
            "completion_tokens": int(completion_tokens_sum),
            "elapsed_sec": float(elapsed_sum),
            "variant_calls": int(n_variants),
            "variant_parallelism": int(variant_workers),
        }
        return (variants, meta)
