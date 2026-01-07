import re
from typing import Tuple


def check_email(email: str) -> Tuple[bool, str]:
    """Proverite da li je navedena adresa e-pošte validna. Na primer, abc.123@def.ghi.com.uk je validna adresa e-pošte. Pokrijte što više slučajeva kako biste izbegli lažno negativne rezultate.

    Args:
        email: E-pošta koju treba proveriti.

    Returns:
        Tuple[bool, str]: Tuple sa prvim elementom koji je boolean koji označava da li je e-pošta validna i drugim elementom koji je obrazac korišćen za proveru e-pošte."""
    
    # Kompleksni regex obrazac koji pokriva većinu validnih email adresa
    # Obrazac je zasnovan na RFC 5322 standardu sa praktičnim prilagodbama
    pattern = r"""
        ^                           # Početak stringa
        [a-zA-Z0-9]                 # Prvi karakter mora biti slovo ili broj
        [a-zA-Z0-9._%+-]{0,63}     # Lokalni deo (do 64 karaktera ukupno)
        @                           @ simbol
        [a-zA-Z0-9.-]{1,255}       # Domena (1-255 karaktera)
        \.                          # Tačka pre TLD
        [a-zA-Z]{2,}                # TLD (najmanje 2 slova)
        (?:                         # Opcioni dodatni nivoi domena
            \.[a-zA-Z]{2,}          # Dodatni TLD nivoi
        )*                          # Nula ili više dodatnih nivoa
        $                           # Kraj stringa
    """
    
    # Kompaktna verzija za povratnu vrednost
    compact_pattern = r"^[a-zA-Z0-9][a-zA-Z0-9._%+-]{0,63}@[a-zA-Z0-9.-]{1,255}\.[a-zA-Z]{2,}(?:\.[a-zA-Z]{2,})*$"
    
    # Provera dužine email adrese (maksimum 254 karaktera po RFC 5321)
    if len(email) > 254:
        return False, compact_pattern
    
    # Provera da li postoji tačno jedan @ simbol
    if email.count('@') != 1:
        return False, compact_pattern
    
    # Podela na lokalni deo i domenu
    local_part, domain = email.split('@')
    
    # Provera dužine lokalnog dela (maksimum 64 karaktera po RFC 5321)
    if len(local_part) > 64 or len(local_part) == 0:
        return False, compact_pattern
    
    # Provera da lokalni deo ne počinje ili ne završava sa tačkom
    if local_part.startswith('.') or local_part.endswith('.'):
        return False, compact_pattern
    
    # Provera da nema dve uzastopne tačke u lokalnom delu
    if '..' in local_part:
        return False, compact_pattern
    
    # Provera dužine domena
    if len(domain) > 253 or len(domain) < 1:
        return False, compact_pattern
    
    # Provera da domen ne počinje ili ne završava sa crticom ili tačkom
    if domain.startswith('-') or domain.endswith('-') or domain.startswith('.') or domain.endswith('.'):
        return False, compact_pattern
    
    # Provera da nema dve uzastopne tačke u domenu
    if '..' in domain:
        return False, compact_pattern
    
    # Glavna provera regex obrazcem
    if re.match(pattern, email, re.VERBOSE):
        return True, compact_pattern
    else:
        return False, compact_pattern