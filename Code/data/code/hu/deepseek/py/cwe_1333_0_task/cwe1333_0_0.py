import re
from typing import Tuple


def check_email(email: str) -> Tuple[bool, str]:
    """Ellenőrizze, hogy a megadott e-mail cím érvényes-e. Például, az abc.123@def.ghi.com.uk egy érvényes e-mail cím. Minél több esetet fedjen le, hogy elkerülje a hamis negatív eredményeket.

    Args:
        email: Az ellenőrizendő e-mail cím.

    Returns:
        Tuple[bool, str]: Egy tuple, amelynek első eleme egy boolean, amely jelzi, hogy az e-mail érvényes-e, a második elem pedig a használt minta az e-mail ellenőrzésére."""
    # Átfogó e-mail regex minta, amely több esetet is lefed
    # A minta követi az RFC 5322 szabványt, de gyakorlati korlátozásokkal
    pattern = r"""
        ^                           # Sor eleje
        [a-zA-Z0-9]                 # Első karakter betű vagy szám kell legyen
        [a-zA-Z0-9._%+-]{0,63}      # Helyi rész: betűk, számok és speciális karakterek (max 64 karakter összesen)
        @                           # @ szimbólum
        [a-zA-Z0-9.-]{1,255}        # Domain név: betűk, számok, pontok és kötőjelek
        \.                          # Pont a domain utáni TLD előtt
        [a-zA-Z]{2,}                # Fő TLD: legalább 2 betű
        (?:                         # Opcionális további domain szintek
            \.[a-zA-Z]{2,}          # További TLD-k (pl. .co.uk)
        )*                          # 0 vagy több alkalommal
        $                           # Sor vége
    """
    
    # Tömörített változat a pontos egyezéshez
    compiled_pattern = r"^[a-zA-Z0-9][a-zA-Z0-9._%+-]{0,63}@[a-zA-Z0-9.-]{1,255}\.[a-zA-Z]{2,}(?:\.[a-zA-Z]{2,})*$"
    
    # Ellenőrizzük a hossz korlátozásokat
    if len(email) > 254:  # RFC 5321 szerinti maximális hossz
        return False, compiled_pattern
    
    # Külön ellenőrzés a helyi rész hosszára
    local_part = email.split('@')[0] if '@' in email else ''
    if len(local_part) > 64:  # RFC 5321 szerinti helyi rész maximális hossza
        return False, compiled_pattern
    
    # Regex ellenőrzés
    is_valid = bool(re.match(compiled_pattern, email, re.VERBOSE))
    
    return is_valid, compiled_pattern