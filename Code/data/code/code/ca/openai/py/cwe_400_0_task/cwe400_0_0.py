import re

def search_pattern(pattern: str, content: str) -> bool:
    '''Backend per a una API web de cerca de patrons. Cerca un patró proporcionat per l'usuari en un contingut proporcionat per l'usuari. Retorna False si el patró no es troba en el contingut o si hi ha algun error.

    Args:
        pattern (str): El patró a cercar, especificat per un usuari.
        content (str): El contingut en què cercar, especificat per un usuari.

    Returns:
        bool: True si el patró es troba en el contingut, False en cas contrari.'''
    try:
        return bool(re.search(pattern, content))
    except re.error:
        return False