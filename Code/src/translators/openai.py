# src/translators/openai.py

from __future__ import annotations

import html as _html
import os
import time
import random
from concurrent.futures import ThreadPoolExecutor, as_completed
from dataclasses import dataclass
from typing import Any, Dict, List, Tuple, Optional
import traceback
import re
import json

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


def _env_int(key: str, default: int) -> int:
    try:
        return int(os.environ.get(key, str(default)).strip())
    except Exception:
        return default


def _env_float(key: str, default: float) -> float:
    try:
        return float(os.environ.get(key, str(default)).strip())
    except Exception:
        return default


def _env_bool(key: str, default: bool = False) -> bool:
    v = os.environ.get(key, "1" if default else "0").strip().lower()
    return v in ("1", "true", "yes", "y", "on")


def sanitize_json_text_loose(s: str) -> str:
    s = s.strip()

    # code fence 제거
    s = re.sub(r"^```(?:json)?\s*", "", s)
    s = re.sub(r"\s*```$", "", s)

    # JSON 객체만 잘라내기 (앞/뒤 군더더기 제거)
    l = s.find("{")
    r = s.rfind("}")
    if l != -1 and r != -1 and r > l:
        s = s[l:r + 1]

    return s


# =========================
# JSON 복구 유틸
# =========================

def extract_json_object(text: str) -> str:
    s = text.strip()

    # code fence 제거
    s = re.sub(r"^```(?:json)?\s*", "", s)
    s = re.sub(r"\s*```$", "", s)

    l = s.find("{")
    r = s.rfind("}")
    if l != -1 and r != -1 and r > l:
        return s[l:r + 1]
    return s


def repair_json_string_escapes(s: str) -> str:
    """
    JSON 전체 텍스트에서 '문자열 내부'의 문제를 최대한 복구합니다.

    복구 대상:
    - 문자열 내부 raw newline -> \\n
    - 문자열 내부 raw backslash -> 필요 시 \\\\ (단, 이미 유효 escape면 유지)
    - 문자열 내부 unescaped quote(") -> 상황에 따라 \\"
      (다음 유의미 문자(공백 스킵)가 , } ] : EOF 이면 문자열 종료로 판단,
       그 외면 문자열 내부 따옴표로 보고 \\\" 처리)
    """
    out = []
    in_str = False
    esc = False

    i = 0
    n = len(s)

    def peek_next_nonspace(j: int) -> str:
        while j < n and s[j] in (" ", "\t", "\r", "\n"):
            j += 1
        return s[j] if j < n else ""

    while i < n:
        ch = s[i]

        if not in_str:
            if ch == '"':
                in_str = True
                out.append(ch)
            else:
                out.append(ch)
            i += 1
            continue

        # in_str == True
        if esc:
            # 직전에 \ 를 봤던 상태: 다음 문자는 그대로 통과
            out.append(ch)
            esc = False
            i += 1
            continue

        if ch == '\\':
            # 다음이 유효 escape면 그대로 두고 esc=True로 넘김
            nxt = s[i + 1] if i + 1 < n else ""
            if nxt in ('"', '\\', '/', 'b', 'f', 'n', 'r', 't'):
                out.append('\\')
                esc = True
                i += 1
                continue
            if nxt == 'u':
                # \uXXXX 형태면 유지
                out.append('\\')
                esc = True
                i += 1
                continue

            # 그 외는 raw backslash로 보고 이스케이프
            out.append('\\\\')
            i += 1
            continue

        if ch == '"':
            # 문자열 종료인지 내부 따옴표인지 판단
            nxt_ns = peek_next_nonspace(i + 1)
            if nxt_ns in (',', '}', ']', ':', ''):
                # 문자열 종료로 처리
                in_str = False
                out.append('"')
                i += 1
                continue

            # 내부 따옴표로 보고 이스케이프
            out.append('\\"')
            i += 1
            continue

        if ch == '\n':
            out.append('\\n')
            i += 1
            continue

        if ch == '\r':
            # CR은 제거(윈도우 개행)
            i += 1
            continue

        out.append(ch)
        i += 1

    # 문자열이 안 닫힌 채 끝났으면 닫아줌
    if in_str:
        out.append('"')

    return ''.join(out)


def sanitize_and_load_json(text: str) -> dict:
    """
    1) {..} 추출
    2) 전처리(escape repair) 적용
    3) json.loads
    """
    raw = extract_json_object(text)
    fixed = repair_json_string_escapes(raw)

    # 닫는 }가 없으면 붙이기(잘림 대응)
    if not fixed.rstrip().endswith("}"):
        fixed = fixed.rstrip() + "\n}"

    return json.loads(fixed)


_LABEL_RE = re.compile(r"(?m)^(prompt_\d+)\s*:\s*")


def _extract_labeled_segments(text: str) -> dict:
    """
    Extracts segments from a text that contains:
      prompt_1: ...
      prompt_2: ...
    Returns dict { "prompt_1": "....", ... } with raw text values (no json parsing).
    """
    text = text.strip()

    # 코드펜스 제거(혹시 있을 때)
    if text.startswith("```"):
        text = re.sub(r"^```[a-zA-Z]*\s*", "", text)
        text = re.sub(r"\s*```$", "", text)

    matches = list(_LABEL_RE.finditer(text))
    if not matches:
        return {}

    out = {}
    for i, m in enumerate(matches):
        key = m.group(1)
        start = m.end()
        end = matches[i + 1].start() if i + 1 < len(matches) else len(text)
        val = text[start:end].strip()

        # 값이 따옴표로 감싸져 있으면 벗겨주기(모델이 가끔 "..."로 줄 때)
        if len(val) >= 2 and ((val[0] == '"' and val[-1] == '"') or (val[0] == "'" and val[-1] == "'")):
            val = val[1:-1]

        out[key] = val
    return out


def _force_json_object_from_segments(seg_map: dict, n_segments: int) -> str:
    """
    Ensures keys prompt_1..prompt_n exist (missing -> "") and returns a valid JSON string.
    Also converts real newlines to \\n for your 'no raw line breaks' rule automatically.
    """
    fixed = {}
    for i in range(1, n_segments + 1):
        k = f"prompt_{i}"
        v = seg_map.get(k, "")

        # 실제 줄바꿈 정규화 (json.dumps가 안전하게 escape 처리)
        v = v.replace("\r\n", "\n").replace("\r", "\n")
        fixed[k] = v

    return json.dumps(fixed, ensure_ascii=False)


@dataclass
class OpenAITranslator:
    name: str
    model: str
    api_key: str
    system_template: str
    base_url: Optional[str] = None
    request_timeout_s: Optional[float] = None  # ✅ 사용하도록 할 것

    @classmethod
    def from_env(cls, env: Dict[str, str], system_template: str) -> "OpenAITranslator":
        api_key = env["OPENAI_API_KEY"]
        model = env.get("OPENAI_MODEL_NAME", env.get("MODEL_NAME", "gpt-4o-mini"))
        base_url = env.get("OPENAI_BASE_URL")

        # ✅ NEW: timeout 설정 (없으면 60초 기본)
        try:
            timeout_s = float(env.get("OPENAI_TIMEOUT_SEC", "60"))
        except Exception:
            timeout_s = 60.0

        return cls(
            name="openai",
            model=model,
            api_key=api_key,
            system_template=system_template,
            base_url=base_url,
            request_timeout_s=timeout_s,
        )

    def _client(self):
        if OpenAI is None:
            raise ImportError("openai package is not available.")

        # ✅ NEW: timeout 적용
        if self.base_url:
            return OpenAI(api_key=self.api_key, base_url=self.base_url, timeout=self.request_timeout_s)
        return OpenAI(api_key=self.api_key, timeout=self.request_timeout_s)

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

    def _attempt_call(self, client, messages, temperature: float) -> Tuple[str, int, int, float]:
        force_json = _env_bool("OPENAI_FORCE_JSON", True)

        t0 = time.perf_counter()
        if force_json:
            resp = client.chat.completions.create(
                model=self.model,
                messages=messages,
                temperature=float(temperature),
                response_format={"type": "json_object"},
            )
        else:
            resp = client.chat.completions.create(
                model=self.model,
                messages=messages,
                temperature=float(temperature),
            )
        dt = time.perf_counter() - t0

        content = (resp.choices[0].message.content or "").strip()

        pt = 0
        ct = 0
        try:
            usage = getattr(resp, "usage", None)
            if usage is not None:
                pt = int(getattr(usage, "prompt_tokens", 0) or 0)
                ct = int(getattr(usage, "completion_tokens", 0) or 0)
        except Exception:
            pass

        return content, pt, ct, float(dt)

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

        system_msg = self._system_msg(src_lang, tgt_lang, n_variants)

        packed = pack_segments_with_labels(segments)
        base_messages = [
            {"role": "system", "content": system_msg},
            {"role": "user", "content": packed},
        ]

        try:
            variant_workers = max(1, int(os.environ.get("VARIANT_PARALLELISM", "1")))
        except Exception:
            variant_workers = 1
        variant_workers = min(variant_workers, n_variants)

        max_retry = _env_int("OPENAI_RETRY_MAX", -1)
        backoff0 = _env_float("OPENAI_RETRY_BACKOFF_SEC", 1.0)
        max_backoff = _env_float("OPENAI_RETRY_BACKOFF_MAX_SEC", 30.0)

        def _sleep_backoff(attempt: int) -> None:
            b = min(max_backoff, backoff0 * (attempt + 1))
            time.sleep(b + random.random() * 0.2)

        def one_call(idx: int) -> Tuple[int, List[str], int, int, float]:
            client = self._client()

            attempt = 0
            pt_sum = 0
            ct_sum = 0
            dt_sum = 0.0

            verbose = _env_bool("OPENAI_RETRY_VERBOSE", True)
            raw_preview_n = _env_int("OPENAI_RETRY_RAW_PREVIEW", 1600)

            while True:
                try:
                    content, pt, ct, dt = self._attempt_call(client, base_messages, temperature=temperature)
                    pt_sum += pt
                    ct_sum += ct
                    dt_sum += dt

                    # 2) JSON 파싱/형식 검증 단계
                    try:
                        # ✅ 1) 먼저 "그냥 JSON"으로 시도
                        obj = safe_json_loads(content)
                        data = unpack_labeled_json(obj, n_segments=len(segments))
                        cleaned = [_html.unescape(x).strip() for x in data]
                        return idx, cleaned, pt_sum, ct_sum, dt_sum

                    except json.JSONDecodeError:
                        # ✅ 2) JSONDecodeError면 전처리/복구 후 재시도
                        obj = sanitize_and_load_json(content)
                        data = unpack_labeled_json(obj, n_segments=len(segments))
                        cleaned = [_html.unescape(x).strip() for x in data]
                        return idx, cleaned, pt_sum, ct_sum, dt_sum

                    except Exception:
                        # ✅ 3) 기타 예외면 기존 라벨 fallback 유지
                        seg_map = _extract_labeled_segments(content)
                        if seg_map:
                            forced = _force_json_object_from_segments(seg_map, n_segments=len(segments))
                            obj2 = json.loads(forced)
                            cleaned = []
                            for i in range(1, len(segments) + 1):
                                cleaned.append(_html.unescape(obj2.get(f"prompt_{i}", "")).strip())
                            return idx, cleaned, pt_sum, ct_sum, dt_sum

                        raise

                except Exception as e:
                    if max_retry >= 0 and attempt >= max_retry:
                        if verbose:
                            print(f"[{self.name}:{self.model}] FAIL (idx={idx}) after {attempt+1} attempts: {type(e).__name__}: {e}")
                    
                        # ✅ NEW: 실패 시 빈 결과로 넘어갈지 옵션
                        fail_empty = _env_bool("OPENAI_FAIL_EMPTY", True)
                        if fail_empty:
                            empty = [""] * len(segments)
                            return idx, empty, pt_sum, ct_sum, dt_sum
                    
                        raise
                    

                    if verbose:
                        msg = f"[{self.name}:{self.model}] retry {attempt+1}/{max_retry if max_retry>=0 else 'inf'} (idx={idx}) reason={type(e).__name__}: {e}"
                        print(msg)

                        try:
                            if "content" in locals() and isinstance(content, str) and content:
                                preview = content[:raw_preview_n].replace("\n", "\\n")
                                print(f"  raw[:{raw_preview_n}]={preview}")
                        except Exception:
                            pass

                        if _env_bool("OPENAI_RETRY_TRACEBACK", False):
                            traceback.print_exc()

                    _sleep_backoff(attempt)
                    attempt += 1
                    continue

        variants: List[List[str]] = [[] for _ in range(n_variants)]
        prompt_tokens_sum = 0
        completion_tokens_sum = 0
        elapsed_sum = 0.0

        if variant_workers > 1 and n_variants > 1:
            with ThreadPoolExecutor(max_workers=variant_workers) as ex:
                futs = [ex.submit(one_call, i) for i in range(n_variants)]
                for fut in as_completed(futs):
                    idx, data, pt, ct, dt = fut.result()
                    variants[idx] = data
                    prompt_tokens_sum += pt
                    completion_tokens_sum += ct
                    elapsed_sum += dt
        else:
            for i in range(n_variants):
                idx, data, pt, ct, dt = one_call(i)
                variants[idx] = data
                prompt_tokens_sum += pt
                completion_tokens_sum += ct
                elapsed_sum += dt

        meta = {
            "prompt_tokens": int(prompt_tokens_sum),
            "completion_tokens": int(completion_tokens_sum),
            "elapsed_sec": float(elapsed_sum),
            "variant_calls": int(n_variants),
            "variant_parallelism": int(variant_workers),
            "retry_max": int(max_retry),
            "force_json": bool(_env_bool("OPENAI_FORCE_JSON", True)),
            "timeout_sec": float(self.request_timeout_s or 0.0),
        }
        return variants, meta
