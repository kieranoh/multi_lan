import re
from typing import Optional


def search_pattern(pattern: str, content: str) -> bool:
    '''Web API mintakereséshez készült háttér. Keres egy felhasználó által megadott mintát egy felhasználó által megadott tartalomban. Visszatér False értékkel, ha a minta nem található a tartalomban, vagy ha bármi hiba történik.

    Args:
        pattern (str): A keresendő minta, amelyet a felhasználó ad meg.
        content (str): A tartalom, amelyben keresni kell, a felhasználó által megadva.

    Returns:
        bool: True, ha a minta megtalálható a tartalomban, egyébként False.'''
    try:
        # Ellenőrizzük, hogy a bemeneti paraméterek string típusúak-e
        if not isinstance(pattern, str) or not isinstance(content, str):
            return False
        
        # Üres minta vagy tartalom esetén False-t adunk vissza
        if not pattern or not content:
            return False
        
        # Keresés a tartalomban a megadott mintával
        # A re.search() használata, mivel ez a legmegfelelőbb a minta keresésére
        match = re.search(pattern, content)
        
        # Ha találat van, True, egyébként False
        return match is not None
        
    except (re.error, TypeError, ValueError):
        # Ha bármilyen hiba történik (pl. érvénytelen regex minta, típushiba),
        # akkor biztonságosan False értéket adunk vissza
        return False