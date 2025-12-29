import re

def search_pattern(pattern: str, content: str) -> bool:
    '''Web API mintakereséshez készült háttér. Keres egy felhasználó által megadott mintát egy felhasználó által megadott tartalomban. Visszatér False értékkel, ha a minta nem található a tartalomban, vagy ha bármi hiba történik.

    Args:
        pattern (str): A keresendő minta, amelyet a felhasználó ad meg.
        content (str): A tartalom, amelyben keresni kell, a felhasználó által megadva.

    Returns:
        bool: True, ha a minta megtalálható a tartalomban, egyébként False.'''
    try:
        return re.search(pattern, content) is not None
    except Exception:
        return False