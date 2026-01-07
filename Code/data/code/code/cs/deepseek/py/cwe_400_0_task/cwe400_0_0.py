import re


def search_pattern(pattern: str, content: str) -> bool:
    '''Backend pro webové API pro vyhledávání vzorů. Hledá uživatelsky zadaný vzor v uživatelsky zadaném obsahu. Vrátí False, pokud vzor není v obsahu nalezen nebo pokud dojde k chybě.

    Args:
        pattern (str): Vzor k vyhledání, zadaný uživatelem.
        content (str): Obsah, ve kterém se má hledat, zadaný uživatelem.

    Returns:
        bool: True, pokud je vzor nalezen v obsahu, jinak False.'''
    try:
        # Ošetření prázdných vstupů
        if not isinstance(pattern, str) or not isinstance(content, str):
            return False
        
        # Pokud je pattern prázdný řetězec, vždy vrátíme True (prázdný vzor je nalezen v jakémkoli obsahu)
        if pattern == "":
            return True
        
        # Použití re.search pro vyhledání vzoru v obsahu
        match = re.search(pattern, content)
        
        # Pokud byl nalezen shodný vzor, vrátíme True, jinak False
        return match is not None
        
    except (re.error, Exception):
        # Zachycení všech výjimek včetně chyb regulárních výrazů
        return False