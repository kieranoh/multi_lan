# src/translators/nllb.py
# -*- coding: utf-8 -*-
from __future__ import annotations

import os

# Keep env cache locations if user provided them (must be set before HF libs init their defaults)
if "HF_HOME" in os.environ:
    os.environ["HF_HOME"] = os.environ["HF_HOME"]
if "TORCH_HOME" in os.environ:
    os.environ["TORCH_HOME"] = os.environ["TORCH_HOME"]

# GPU selection (prefer NLLB_CUDA_VISIBLE_DEVICES, fallback NLLB_GPU)
_gpu_sel = os.environ.get("NLLB_CUDA_VISIBLE_DEVICES") 
if _gpu_sel is not None and str(_gpu_sel).strip() != "":
    os.environ["CUDA_VISIBLE_DEVICES"] = str(_gpu_sel).strip()

import time
from dataclasses import dataclass
from typing import Any, Dict, List, Tuple, Optional

try:
    from transformers import AutoModelForSeq2SeqLM, AutoTokenizer
except Exception:
    AutoModelForSeq2SeqLM = None  # type: ignore
    AutoTokenizer = None  # type: ignore

try:
    import torch
except Exception:
    torch = None  # type: ignore


NLLB_LANG: Dict[str, str] = {
    
    # ---- level 0 ----
    "kac": "kac_Latn",    # Jingpho
    "ndo": "ndo_Latn",    # Ndonga
    "dyu": "dyu_Latn",    # Dyula
    "bua": "bua_Cyrl",   # Buriat
    "lis": "lis_Latn",   # Lisu
    "tig": "tig_Ethi",   # Tigré
    "ful": "ful_Latn",   # Fula

    # ---- level 1 ----
    "tel": "tel_Telu",   # Telugu
    "som": "som_Latn",   # Somali
    "gla": "gla_Latn",   # Scottish Gaelic
    "ibo": "ibo_Latn",   # Igbo
    "bam": "bam_Latn",   # Bambara
    "asm": "asm_Beng",   # Assamese
    "sqi": "sqi_Latn",   # Albanian

    # ---- level 2 ----
    "pnb": "pnb_Arab",   # Western Punjabi
    "hau": "hau_Latn",   # Hausa
    "mar": "mar_Deva",   # Marathi
    "xho": "xho_Latn",   # Xhosa
    "swa": "swa_Latn",   # Swahili
    "san": "san_Deva",   # Sanskrit
    "zul": "zul_Latn",   # Zulu

    # ---- level 3 ----
    "ukr": "ukr_Cyrl",   # Ukrainian
    "ceb": "ceb_Latn",   # Cebuano
    "arz": "arz_Arab",   # Egyptian Arabic
    "lav": "lav_Latn",   # Latvian
    "ind": "ind_Latn",   # Indonesian
    "afr": "afr_Latn",   # Afrikaans
    "bos": "bos_Latn",   # Bosnian

     # -------- level 4  --------
    "sv": "swe_Latn",      
    "tr": "tur_Latn",      
    "ko": "kor_Hang",      
    "hi": "hin_Deva",      
    "pt": "por_Latn",      
    "ru": "rus_Cyrl",      
    "nl": "nld_Latn",      
    "pl": "pol_Latn",      
    "it": "ita_Latn",      
    "fi": "fin_Latn",      
    "hu": "hun_Latn",      
    "cs": "ces_Latn",     
    "vi": "vie_Latn",     
    "hr": "hrv_Latn",      
    "sr": "srp_Cyrl",      
    "ca": "cat_Latn",     
    "eu": "eus_Latn",      
    "fa": "pes_Arab",     
    
    # -------- level 5  --------
    "en": "eng_Latn",      
    "es": "spa_Latn",      
    "de": "deu_Latn",      
    "fr": "fra_Latn",      
    "ja": "jpn_Jpan",      
    "zh": "zho_Hans",       
    "ar": "arb_Arab",      
}


@dataclass
class NLLBTranslator:
    name: str = "nllb"
    model_name: str = "facebook/nllb-200-distilled-600M"
    device: Optional[str] = None  # "cuda" / "cpu" / "cuda:0" etc.

    def __post_init__(self):
        if AutoTokenizer is None or AutoModelForSeq2SeqLM is None:
            raise ImportError("transformers is not available. Install: pip install transformers sentencepiece")
        if torch is None:
            raise ImportError("torch is not available.")

        self.tokenizer = AutoTokenizer.from_pretrained(self.model_name)
        self.model = AutoModelForSeq2SeqLM.from_pretrained(self.model_name)

        if self.device is None:
            self.device = "cuda" if hasattr(torch, "cuda") and torch.cuda.is_available() else "cpu"

        self.model.to(self.device)
        self.model.eval()

    @classmethod
    def from_env(cls, env: Dict[str, str]) -> "NLLBTranslator":
        model_name = env.get("NLLB_MODEL_NAME", "facebook/nllb-200-distilled-600M")
        device = env.get("NLLB_DEVICE")

        gpu_sel = env.get("NLLB_CUDA_VISIBLE_DEVICES") or env.get("NLLB_GPU")
        if gpu_sel is not None and str(gpu_sel).strip() != "":
            os.environ["CUDA_VISIBLE_DEVICES"] = str(gpu_sel).strip()

        return cls(model_name=model_name, device=device)

    def _translate_n(self, text: str, src_lang: str, tgt_lang: str, n: int) -> List[str]:
        if not text.strip():
            return ["" for _ in range(n)]
        if src_lang not in NLLB_LANG or tgt_lang not in NLLB_LANG:
            raise ValueError(f"[nllb] unsupported lang: {src_lang}->{tgt_lang}")

        self.tokenizer.src_lang = NLLB_LANG[src_lang]
        encoded = self.tokenizer(text, return_tensors="pt", truncation=True)
        encoded = {k: v.to(self.device) for k, v in encoded.items()}

        tgt_code = NLLB_LANG[tgt_lang]

        # ✅ NLLB 권장: lang_code_to_id 사용
        lang2id = getattr(self.tokenizer, "lang_code_to_id", None)
        if isinstance(lang2id, dict) and tgt_code in lang2id:
            forced_bos_token_id = lang2id[tgt_code]
        else:
            # fallback: convert_tokens_to_ids (but guard unk)
            forced_bos_token_id = self.tokenizer.convert_tokens_to_ids(tgt_code)
        
        unk_id = getattr(self.tokenizer, "unk_token_id", None)
        if unk_id is not None and forced_bos_token_id == unk_id:
            raise ValueError(f"[nllb] target lang token not found in tokenizer vocab: {tgt_code}")

        gen = self.model.generate(
            **encoded,
            forced_bos_token_id=forced_bos_token_id,
            max_new_tokens=512,
            num_beams=n,
            num_return_sequences=n,
            do_sample=False,
        )
        outs = self.tokenizer.batch_decode(gen, skip_special_tokens=True)
        if len(outs) == 1 and n > 1:
            outs = outs * n
        return [o.strip() for o in outs[:n]]

    def translate_prompt_variants(
        self,
        segments: List[str],
        src_lang: str,
        tgt_lang: str,
        n_variants: int,
        temperature: float,
    ) -> Tuple[List[List[str]], Dict[str, Any]]:
        _ = temperature  # API 호환용 (NLLB는 사용 안 함)

        if not segments:
            return ([[] for _ in range(n_variants)], {"elapsed_sec": 0.0})

        t0 = time.perf_counter()
        segs_by_variant: List[List[str]] = [[] for _ in range(n_variants)]
        for seg in segments:
            variants = self._translate_n(seg, src_lang=src_lang, tgt_lang=tgt_lang, n=n_variants)
            for i in range(n_variants):
                segs_by_variant[i].append(variants[i])
        dt = time.perf_counter() - t0
        return (segs_by_variant, {"elapsed_sec": float(dt)})
