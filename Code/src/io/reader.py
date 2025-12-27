# -*- coding: utf-8 -*-
from __future__ import annotations

import json
from pathlib import Path
from typing import Any, Dict, List


def read_jsonl(path: Path) -> List[Dict[str, Any]]:
    recs: List[Dict[str, Any]] = []
    with path.open("r", encoding="utf-8") as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            recs.append(json.loads(line))
    return recs


def list_en_jsonl_files(prompts_dir: Path) -> List[Path]:
    return sorted([p for p in prompts_dir.iterdir() if p.is_file() and p.name.endswith("en.jsonl")])
