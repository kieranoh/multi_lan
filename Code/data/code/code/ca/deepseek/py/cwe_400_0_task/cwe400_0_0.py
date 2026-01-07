import re


def search_pattern(pattern: str, content: str) -> bool:
    '''Backend per a una API web de cerca de patrons. Cerca un patró proporcionat per l'usuari en un contingut proporcionat per l'usuari. Retorna False si el patró no es troba en el contingut o si hi ha algun error.

    Args:
        pattern (str): El patró a cercar, especificat per un usuari.
        content (str): El contingut en què cercar, especificat per un usuari.

    Returns:
        bool: True si el patró es troba en el contingut, False en cas contrari.'''
    try:
        # Comprovar si el patró o el contingut són buits
        if not pattern or not content:
            return False
        
        # Cercar el patró en el contingut
        match = re.search(pattern, content)
        
        # Retornar True si s'ha trobat una coincidència, False en cas contrari
        return bool(match)
    except (re.error, TypeError, ValueError):
        # Capturar errors de regex, tipus o valors invàlids
        return False