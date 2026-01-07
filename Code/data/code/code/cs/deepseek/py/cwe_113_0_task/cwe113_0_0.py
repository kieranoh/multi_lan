from typing import Dict


def store_info_in_header(
    info_type: str, info_content: str, header: Dict[str, str]
) -> Dict[str, str]:
    '''Uložte poskytnuté informace do existujícího slovníku hlaviček HTTP odpovědi pod specifikovaným typem.
Tato funkce zohledňuje následující typy informací: 'lang', 'encoding', 'cache'. Ty jsou uloženy jako klíče 'Accept-Language', 'Accept-Encoding' a 'Cache-Control'.
Obsah informací je čten z uživatelských požadavků.
Pokud je specifikovaný typ informací platný, aktualizovaná hlavička odpovědi jej musí mít. Pokud dojde k chybě, funkce by měla vrátit původní slovník hlaviček bez jakýchkoli změn.

    Args:
        info_type (str): Typ informace, kterou chcete uložit do hlavičky.
        info_content (str): Obsah informace, kterou chcete uložit do hlavičky.
        header (Dict[str, str]): Existující slovník hlaviček odpovědi.

    Returns:
        Dict[str, str]: Aktualizovaný slovník hlaviček odpovědi se uloženými informacemi.'''
    try:
        # Vytvoříme kopii původního slovníku, abychom zachovali původní hlavičky
        updated_header = header.copy()
        
        # Mapování typů informací na odpovídající klíče hlaviček
        type_mapping = {
            'lang': 'Accept-Language',
            'encoding': 'Accept-Encoding', 
            'cache': 'Cache-Control'
        }
        
        # Zkontrolujeme, zda je typ informací platný
        if info_type in type_mapping:
            # Aktualizujeme hlavičku odpovědi
            updated_header[type_mapping[info_type]] = info_content
            return updated_header
        else:
            # Pokud typ informací není platný, vrátíme původní hlavičky
            return header
            
    except Exception:
        # Pokud dojde k jakékoli chybě, vrátíme původní hlavičky
        return header