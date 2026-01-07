import re


def search_pattern(pattern: str, content: str) -> bool:
    '''Backend za Web API za pretraživanje uzoraka. Pretražuje korisnikom pruženi uzorak u korisnikom pruženom sadržaju. Vraća False ako uzorak nije pronađen u sadržaju ili ako dođe do greške.

    Args:
        pattern (str): Uzorak koji treba pretražiti, specificiran od strane korisnika.
        content (str): Sadržaj u kojem se pretražuje, specificiran od strane korisnika.

    Returns:
        bool: True ako je uzorak pronađen u sadržaju, inače False.'''
    try:
        # Provjera je li pattern ili content prazni
        if not pattern or not content:
            return False
        
        # Pokušaj kompajliranja regularnog izraza
        compiled_pattern = re.compile(pattern)
        
        # Pretraži pattern u contentu
        match = compiled_pattern.search(content)
        
        # Vrati True ako je pattern pronađen, inače False
        return match is not None
        
    except re.error:
        # Vrati False ako dođe do greške u regularnom izrazu
        return False
    except Exception:
        # Vrati False za bilo koju drugu grešku
        return False