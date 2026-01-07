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
        # Ellenőrizzük, hogy a header érvényes szótár-e
        if not isinstance(header, dict):
            return header
        
        # Érvényes info_type-ok és a hozzájuk tartozó header kulcsok
        valid_types = {
            'lang': 'Accept-Language',
            'encoding': 'Accept-Encoding', 
            'cache': 'Cache-Control'
        }
        
        # Ellenőrizzük, hogy az info_type érvényes-e
        if info_type not in valid_types:
            return header
        
        # Ellenőrizzük, hogy az info_content nem üres string-e
        if not isinstance(info_content, str) or info_content.strip() == '':
            return header
        
        # Létrehozunk egy másolatot a header szótárról, hogy ne módosítsuk az eredetit
        updated_header = header.copy()
        
        # Beállítjuk a megfelelő kulcsot az info_content értékével
        header_key = valid_types[info_type]
        updated_header[header_key] = info_content.strip()
        
        return updated_header
        
    except Exception:
        # Bármilyen hiba esetén visszaadjuk az eredeti headert
        return header