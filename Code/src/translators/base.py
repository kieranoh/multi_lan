# -*- coding: utf-8 -*-
from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path
from typing import Any, Dict, List, Tuple, Protocol

from src.postprocess.preserve_code import LANG_MAP


class Translator(Protocol):
    name: str

    def translate_prompt_variants(
        self,
        segments: List[str],
        src_lang: str,
        tgt_lang: str,
        n_variants: int,
        temperature: float,
    ) -> Tuple[List[List[str]], Dict[str, Any]]:
        """Return (variants x segments, usage/meta dict)."""
        ...


def get_num_variants(module_name: str, env: Dict[str, str]) -> int:
    m = module_name.strip().lower()
    if m == "openai":
        return int(env.get("N_VARIANTS_OPENAI", "3"))
    if m == "deepseek":
        return int(env.get("N_VARIANTS_DEEPSEEK", "5"))
    if m == "nllb":
        return int(env.get("N_VARIANTS_NLLB", "5"))
    return int(env.get("N_VARIANTS_DEFAULT", "4"))


def compute_cost_usd(
    module: str,
    prompt_tokens: int,
    completion_tokens: int,
    env: Dict[str, str],
) -> float | None:
    module = module.lower()
    if module == "openai":
        in_rate = env.get("OPENAI_INPUT_COST_PER_1M")
        out_rate = env.get("OPENAI_OUTPUT_COST_PER_1M")
    elif module == "deepseek":
        in_rate = env.get("DEEPSEEK_INPUT_COST_PER_1M")
        out_rate = env.get("DEEPSEEK_OUTPUT_COST_PER_1M")
    else:
        return None

    if not in_rate or not out_rate:
        return None

    in_rate_f = float(in_rate)
    out_rate_f = float(out_rate)
    return (prompt_tokens / 1_000_000.0) * in_rate_f + (completion_tokens / 1_000_000.0) * out_rate_f


def load_system_template(base_prompt_path: Path) -> str:
    return base_prompt_path.read_text(encoding="utf-8")


def validate_lang_pair(src_lang: str, tgt_lang: str) -> None:
    if src_lang not in LANG_MAP or tgt_lang not in LANG_MAP:
        raise ValueError(f"Unknown language code: {src_lang}->{tgt_lang}")


def build_translator(module_name: str, env: Dict[str, str], base_prompt_path: Path) -> Translator:
    module_name = module_name.strip().lower()
    system_template = load_system_template(base_prompt_path)

    if module_name == "openai":
        from src.translators.openai import OpenAITranslator
        return OpenAITranslator.from_env(env=env, system_template=system_template)

    if module_name == "deepseek":
        from src.translators.deepseek import DeepSeekTranslator
        return DeepSeekTranslator.from_env(env=env, system_template=system_template)

    if module_name == "nllb":
        from src.translators.nllb import NLLBTranslator
        return NLLBTranslator.from_env(env=env)

    raise ValueError(f"Unknown translation module: {module_name}")
