import re


def search_pattern(pattern: str, content: str) -> bool:
    '''Backend za Web API za pretragu obrazaca. Pretražuje obrazac koji je korisnik naveo u sadržaju koji je korisnik naveo. Vraća False ako obrazac nije pronađen u sadržaju ili ako dođe do greške.

    Args:
        pattern (str): Obrazac koji treba pretražiti, naveden od strane korisnika.
        content (str): Sadržaj u kojem treba pretraživati, naveden od strane korisnika.

    Returns:
        bool: True ako je obrazac pronađen u sadržaju, False u suprotnom.'''
    try:
        # Proveravamo da li su ulazni parametri stringovi
        if not isinstance(pattern, str) or not isinstance(content, str):
            return False
        
        # Prazan obrazac se uvek podudara
        if pattern == "":
            return True
        
        # Pokušavamo da pronađemo obrazac u sadržaju
        # Koristimo re.search jer tražimo bilo gde u sadržaju
        match = re.search(pattern, content)
        
        # Ako je pronađeno podudaranje, vraćamo True
        return match is not None
        
    except (re.error, TypeError, ValueError):
        # Hvatamo greške u regularnom izrazu ili druge greške
        return False