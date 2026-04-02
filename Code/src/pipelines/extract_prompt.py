# -*- coding: utf-8 -*-
from __future__ import annotations

import os
import json
from pathlib import Path
from typing import Any, Dict, List

from dotenv import load_dotenv

# CWEval prompt definitions
from data.raw.CWEval_ppt import DirectPrompt, SecurePrompt, DirectCompletionPrompt  # type: ignore


def _protect_placeholders(s: str) -> str:
    """
    Protect {lang}, {code_prompt}, {lang_instr} so the translator won't touch them.
    We wrap them with backticks. Later we will unprotect at generation time.
    """
    return (
        s.replace("{lang_instr}", "`{lang_instr}`")
         .replace("{lang}", "`{lang}`")
         .replace("{code_prompt}", "`{code_prompt}`")
    )


def _emit_templates_for_prompt_class(cls, ppt_name: str) -> List[Dict[str, Any]]:
    """
    Create one template per language key in LANG_INSTR.
    task: ppt_<ppt_name>_<lang>
    prompt: cls.PPT with lang/lang_instr filled, but code_prompt kept as placeholder.
    """
    out: List[Dict[str, Any]] = []
    for lang, lang_instr in cls.LANG_INSTR.items():
        # Fill lang/lang_instr, keep {code_prompt} placeholder
        ppt = cls.PPT
        # protect placeholders first (lang, lang_instr, code_prompt)
        ppt2 = _protect_placeholders(ppt)

        # Now we want to "apply" lang/lang_instr values but keep `{code_prompt}` as-is.
        # Because we protected placeholders, we replace the protected `{lang}`/`{lang_instr}` first.
        filled = (
            ppt2.replace("`{lang}`", lang)
               .replace("`{lang_instr}`", _protect_placeholders(lang_instr))  # lang_instr itself may contain braces? protect anyway
        )

        # Keep `{code_prompt}` protected placeholder.
        task = f"ppt_{ppt_name}_{lang}"
        out.append(
            {
                "task": task,
                "lang": lang,      # code language (c/go/py/...)
                "prompt": filled,  # English template to translate
            }
        )
    return out


def main() -> None:
    load_dotenv()
    env = dict(os.environ)

    dataset = env.get("TARGET_DATASET", "CWEVAL").strip()
    ds_upper = dataset.upper()

    prompts_dir = Path(env[f"{ds_upper}_PROMPTS_DIR"]).resolve()
    prompts_dir.mkdir(parents=True, exist_ok=True)

    out_path = prompts_dir / "gen_prompt_templates_en.jsonl"

    recs: List[Dict[str, Any]] = []
    recs += _emit_templates_for_prompt_class(DirectPrompt, "direct")
    recs += _emit_templates_for_prompt_class(SecurePrompt, "secure")
    recs += _emit_templates_for_prompt_class(DirectCompletionPrompt, "compl")

    with out_path.open("w", encoding="utf-8") as f:
        for r in recs:
            f.write(json.dumps(r, ensure_ascii=False) + "\n")

    print(f"[DONE] wrote {len(recs)} gen prompt templates: {out_path}")


if __name__ == "__main__":
    main()
