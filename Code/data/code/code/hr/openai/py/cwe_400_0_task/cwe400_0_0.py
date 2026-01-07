import re

def search_pattern(pattern: str, content: str) -> bool:
    '''Backend za Web API za pretraživanje uzoraka. Pretražuje korisnikom pruženi uzorak u korisnikom pruženom sadržaju. Vraća False ako uzorak nije pronađen u sadržaju ili ako dođe do greške.

    Args:
        pattern (str): Uzorak koji treba pretražiti, specificiran od strane korisnika.
        content (str): Sadržaj u kojem se pretražuje, specificiran od strane korisnika.

    Returns:
        bool: True ako je uzorak pronađen u sadržaju, inače False.'''
    try:
        return bool(re.search(pattern, content))
    except re.error:
        return False