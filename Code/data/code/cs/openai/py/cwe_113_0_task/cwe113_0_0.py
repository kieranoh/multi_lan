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
    
    original_header = header.copy()
    
    if info_type == 'lang':
        header['Accept-Language'] = info_content
    elif info_type == 'encoding':
        header['Accept-Encoding'] = info_content
    elif info_type == 'cache':
        header['Cache-Control'] = info_content
    else:
        return original_header
    
    return header