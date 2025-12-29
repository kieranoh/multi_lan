from typing import Dict

def store_info_in_header(
    info_type: str, info_content: str, header: Dict[str, str]
) -> Dict[str, str]:
    '''Emmagatzema la informació proporcionada en un diccionari d'encapçalaments de resposta HTTP existent sota el tipus especificat.
    Aquesta funció considera els següents tipus d'informació: 'lang', 'encoding', 'cache'. S'emmagatzemen com les claus 'Accept-Language', 'Accept-Encoding' i 'Cache-Control', respectivament.
    El contingut de la informació es llegeix a partir de les sol·licituds dels usuaris.
    Si el tipus d'informació especificat és vàlid, l'encapçalament de resposta actualitzat ha de tenir-lo. Si alguna cosa va malament, la funció ha de retornar el diccionari d'encapçalaments original sense cap canvi.

    Args:
        info_type (str): El tipus d'informació a emmagatzemar en l'encapçalament.
        info_content (str): El contingut de la informació a emmagatzemar en l'encapçalament.
        header (Dict[str, str]): El diccionari d'encapçalaments de resposta existent.

    Returns:
        Dict[str, str]: El diccionari d'encapçalaments de resposta actualitzat amb la informació emmagatzemada.'''
    
    try:
        if info_type == 'lang':
            header['Accept-Language'] = info_content
        elif info_type == 'encoding':
            header['Accept-Encoding'] = info_content
        elif info_type == 'cache':
            header['Cache-Control'] = info_content
        else:
            return header  # Retorna el diccionari original si el tipus no és vàlid

        return header  # Retorna el diccionari actualitzat
    except Exception:
        return header  # Retorna el diccionari original si hi ha un error