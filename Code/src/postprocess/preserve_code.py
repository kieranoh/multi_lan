# -*- coding: utf-8 -*-
from __future__ import annotations

import json
import re
from typing import Any, Dict, List, Tuple

PY_TRIPLE_DOUBLE = re.compile(r'"""(.*?)"""', re.DOTALL)
PY_TRIPLE_SINGLE = re.compile(r"\'\'\'(.*?)\'\'\'", re.DOTALL)

C_BLOCK_DOC = re.compile(r"/\*\*(.*?)\*/", re.DOTALL)  # /** ... */
C_BLOCK = re.compile(r"/\*(?!\*)(.*?)\*/", re.DOTALL)   # /* ... */ but NOT /** ... */
CLINE_BLOCK = re.compile(r"((?:^\s*//.*\n?)+)", re.MULTILINE)


LANG_MAP: Dict[str, str] = {
    # ---- level 4 ----
    "sv": "Swedish",
    "tr": "Turkish",
    "ko": "Korean",
    "hi": "Hindi",
    "fa": "Persian",
    "pt": "Portuguese",
    "cs": "Czech",
    "ru": "Russian",
    "nl": "Dutch",
    "pl": "Polish",
    "hr": "Croatian",
    "it": "Italian",
    "vi": "Vietnamese",
    "eu": "Basque",
    "hu": "Hungarian",
    "fi": "Finnish",
    "sr": "Serbian",
    "ca": "Catalan",

    # ---- level 5 ----
    "en": "English",
    "es": "Spanish",
    "de": "German",
    "ja": "Japanese",
    "fr": "French",
    "ar": "Arabic",
    "zh": "Chinese",
}


def pack_segments_with_labels(segments: List[str]) -> str:
    parts = []
    for i, seg in enumerate(segments, start=1):
        parts.append(f"prompt_{i}: {seg}".rstrip())
    return "\n\n".join(parts).strip()


def unpack_labeled_json(obj: Any, n_segments: int) -> List[str]:
    if not isinstance(obj, dict):
        raise ValueError("Model output must be a JSON object (dict).")
    out: List[str] = []
    for i in range(1, n_segments + 1):
        k = f"prompt_{i}"
        v = obj.get(k)
        if not isinstance(v, str):
            raise ValueError(f"Missing/invalid key: {k}")
        out.append(v.strip())
    return out


def safe_json_loads(text: str) -> Any:
    if not text:
        raise ValueError("Empty response from model")
    t = text.strip()

    # strip ```json fences
    if t.startswith("```"):
        t = re.sub(r"^```(?:json)?", "", t).strip()
        t = re.sub(r"```$", "", t).strip()

    # strip leading junk before first { or [
    brace = t.find("{")
    bracket = t.find("[")
    starts = [x for x in [brace, bracket] if x != -1]
    if starts:
        t = t[min(starts):].strip()

    return json.loads(t)


def _find_all_blocks(full_prompt: str, lang: str) -> List[Tuple[Tuple[int, int], str, str]]:
    lang = (lang or "").lower()
    blocks: List[Tuple[Tuple[int, int], str, str]] = []

    # Python
    if lang in {"py", "python"}:
        for m in PY_TRIPLE_DOUBLE.finditer(full_prompt):
            blocks.append((m.span(0), m.group(1), '"""{PROMPT_i}"""'))
        for m in PY_TRIPLE_SINGLE.finditer(full_prompt):
            blocks.append((m.span(0), m.group(1), "'''{PROMPT_i}'''"))
        blocks.sort(key=lambda x: x[0][0])
        return blocks

    # C-like
    if lang in {"c", "cpp", "c++", "cc", "h", "hpp", "go", "js", "javascript"}:
        for m in C_BLOCK_DOC.finditer(full_prompt):
            blocks.append((m.span(0), m.group(1), "/* {PROMPT_i} */"))
        for m in C_BLOCK.finditer(full_prompt):
            blocks.append((m.span(0), m.group(1), "/* {PROMPT_i} */"))
        for m in CLINE_BLOCK.finditer(full_prompt):
            start0, end0 = m.span(1)
            block = m.group(1)
            lines = block.splitlines()
            inner = "\n".join(re.sub(r"^\s*//\s?", "", ln) for ln in lines)
            first = lines[0] if lines else "// "
            m_pref = re.match(r"^(\s*//\s*)", first)
            prefix = m_pref.group(1) if m_pref else "// "
            replacement = prefix + "{PROMPT_i}"
            blocks.append(((start0, end0), inner, replacement))
        blocks.sort(key=lambda x: x[0][0])
        return blocks

    # Fallback: try all
    tmp: List[Tuple[Tuple[int, int], str, str]] = []
    for m in PY_TRIPLE_DOUBLE.finditer(full_prompt):
        tmp.append((m.span(0), m.group(1), '"""{PROMPT_i}"""'))
    for m in PY_TRIPLE_SINGLE.finditer(full_prompt):
        tmp.append((m.span(0), m.group(1), "'''{PROMPT_i}'''"))
    for m in C_BLOCK_DOC.finditer(full_prompt):
        tmp.append((m.span(0), m.group(1), "/* {PROMPT_i} */"))
    for m in C_BLOCK.finditer(full_prompt):
        tmp.append((m.span(0), m.group(1), "/* {PROMPT_i} */"))
    for m in CLINE_BLOCK.finditer(full_prompt):
        start0, end0 = m.span(1)
        lines = m.group(1).splitlines()
        inner = "\n".join(re.sub(r"^\s*//\s?", "", ln) for ln in lines)
        first = lines[0] if lines else "// "
        m_pref = re.match(r"^(\s*//\s*)", first)
        prefix = m_pref.group(1) if m_pref else "// "
        tmp.append(((start0, end0), inner, prefix + "{PROMPT_i}"))

    tmp.sort(key=lambda x: x[0][0])
    return tmp


def extract_code_and_prompts(full_prompt: str, lang: str) -> Tuple[str, List[str]]:
    blocks = _find_all_blocks(full_prompt, lang)
    if not blocks:
        return full_prompt, []

    code_parts: List[str] = []
    prompts: List[str] = []
    last_idx = 0

    for i, (span, inner, replacement) in enumerate(blocks, start=1):
        s, e = span
        code_parts.append(full_prompt[last_idx:s])
        rep = replacement.replace("{PROMPT_i}", f"{{PROMPT_{i}}}")
        code_parts.append(rep)
        prompts.append(inner.strip("\n"))
        last_idx = e

    code_parts.append(full_prompt[last_idx:])
    return "".join(code_parts), prompts


def fill_code_template(code_template: str, prompt_segments: List[str]) -> str:
    out = code_template
    for i, seg in enumerate(prompt_segments, start=1):
        out = out.replace(f"{{PROMPT_{i}}}", seg)
    return out
