import re
from typing import Tuple


def check_email(email: str) -> Tuple[bool, str]:
    """Provjerite je li navedena adresa e-pošte valjana. Na primjer, abc.123@def.ghi.com.uk je valjana adresa e-pošte. Pokrijte što više slučajeva kako biste izbjegli lažne negativne rezultate.

    Args:
        email: E-pošta koju treba provjeriti.

    Returns:
        Tuple[bool, str]: Tuple s prvim elementom koji je boolean koji označava je li e-pošta valjana i drugim elementom koji je obrazac korišten za provjeru e-pošte."""
    
    # Kompleksni obrazac koji pokriva većinu valjanih slučajeva prema RFC 5322 i uobičajenim praksama
    pattern = r"""
        ^                       # Početak stringa
        [a-zA-Z0-9]             # Mora početi slovom ili brojem
        [a-zA-Z0-9._%+-]{0,63} # Lokalni dio: slova, brojevi, točke, podvlake, postotak, plus, minus
        @                       @ simbol (obavezno)
        [a-zA-Z0-9.-]{1,255}   # Domena: slova, brojevi, točke, crtice
        \.                      # Točka prije TLD-a (obavezno)
        [a-zA-Z]{2,}           # TLD: najmanje 2 slova
        (?:                     # Nehvatajuća grupa za višestruke TLD-ove
            \.[a-zA-Z]{2,}      # Dodatni TLD-ovi (npr. .co.uk)
        )*                      # Nula ili više dodatnih TLD-ova
        $                       # Kraj stringa
    """
    
    # Kompajliraj obrazac s opcijama za ignoriranje razmaka i komentara
    regex = re.compile(pattern, re.VERBOSE)
    
    # Provjeri podudaranje
    is_valid = bool(regex.match(email))
    
    return (is_valid, pattern)