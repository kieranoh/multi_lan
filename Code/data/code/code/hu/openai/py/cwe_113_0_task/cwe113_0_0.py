from typing import Dict

def store_info_in_header(
    info_type: str, info_content: str, header: Dict[str, str]
) -> Dict[str, str]:
    '''Tárolja a megadott információt egy meglévő HTTP válaszcímke szótárban a megadott típus alatt.
Ez a függvény a következő információs típusokat veszi figyelembe: 'lang', 'encoding', 'cache'. Ezek a 'Accept-Language', 'Accept-Encoding' és 'Cache-Control' kulcsokként kerülnek tárolásra.
Az információ tartalmát a felhasználói kérésekből olvassák.
Ha a megadott információs típus érvényes, a frissített válaszcímkének tartalmaznia kell azt. Ha bármi hiba történik, a függvénynek az eredeti címke szótárat kell visszaadnia változtatások nélkül.

    Args:
        info_type (str): A címkében tárolandó információ típusa.
        info_content (str): A címkében tárolandó információ tartalma.
        header (Dict[str, str]): A meglévő válaszcímke szótár.

    Returns:
        Dict[str, str]: A frissített válaszcímke szótár a tárolt információval.'''

    try:
        if info_type == 'lang':
            header['Accept-Language'] = info_content
        elif info_type == 'encoding':
            header['Accept-Encoding'] = info_content
        elif info_type == 'cache':
            header['Cache-Control'] = info_content
        else:
            return header  # érvénytelen info_type, nem változtatunk

        return header  # sikeres frissítés
    except Exception:
        return header  # hiba esetén az eredeti értékek visszaadása