import re


def search_pattern(pattern: str, content: str) -> bool:
    '''Backend za Web API za pretragu obrazaca. Pretražuje obrazac koji je korisnik naveo u sadržaju koji je korisnik naveo. Vraća False ako obrazac nije pronađen u sadržaju ili ako dođe do greške.

    Args:
        pattern (str): Obrazac koji treba pretražiti, naveden od strane korisnika.
        content (str): Sadržaj u kojem treba pretraživati, naveden od strane korisnika.

    Returns:
        bool: True ako je obrazac pronađen u sadržaju, False u suprotnom.'''
    try:
        return re.search(pattern, content) is not None
    except re.error:
        return False