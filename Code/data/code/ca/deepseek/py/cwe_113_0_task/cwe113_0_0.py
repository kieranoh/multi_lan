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
    # Crear una còpia del diccionari d'encapçalaments per no modificar l'original directament
    updated_header = header.copy()
    
    # Mapejar els tipus d'informació vàlids a les claus d'encapçalament corresponents
    valid_mappings = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding',
        'cache': 'Cache-Control'
    }
    
    # Verificar si el tipus d'informació és vàlid
    if info_type in valid_mappings:
        try:
            # Obtenir la clau d'encapçalament corresponent
            header_key = valid_mappings[info_type]
            # Actualitzar l'encapçalament amb el contingut proporcionat
            updated_header[header_key] = info_content
            return updated_header
        except Exception:
            # Si alguna cosa va malament, retornar l'encapçalament original
            return header
    else:
        # Si el tipus no és vàlid, retornar l'encapçalament original
        return header