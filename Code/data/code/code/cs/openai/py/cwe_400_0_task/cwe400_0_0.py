import re

def search_pattern(pattern: str, content: str) -> bool:
    '''Backend pro webové API pro vyhledávání vzorů. Hledá uživatelsky zadaný vzor v uživatelsky zadaném obsahu. Vrátí False, pokud vzor není v obsahu nalezen nebo pokud dojde k chybě.

    Args:
        pattern (str): Vzor k vyhledání, zadaný uživatelem.
        content (str): Obsah, ve kterém se má hledat, zadaný uživatelem.

    Returns:
        bool: True, pokud je vzor nalezen v obsahu, jinak False.'''
    try:
        return re.search(pattern, content) is not None
    except re.error:
        return False