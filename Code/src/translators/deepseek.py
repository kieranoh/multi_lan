# -*- coding: utf-8 -*-
from __future__ import annotations

from dataclasses import dataclass
from typing import Dict

from src.translators.openai import OpenAITranslator


@dataclass
class DeepSeekTranslator(OpenAITranslator):
    @classmethod
    def from_env(cls, env: Dict[str, str], system_template: str) -> "DeepSeekTranslator":
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
