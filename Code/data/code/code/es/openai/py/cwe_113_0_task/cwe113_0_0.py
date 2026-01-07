from typing import Dict

def store_info_in_header(
    info_type: str, info_content: str, header: Dict[str, str]
) -> Dict[str, str]:
    '''Almacena la información proporcionada en un diccionario de encabezados de respuesta HTTP existente bajo el tipo especificado.
    Esta función considera los siguientes tipos de información: 'lang', 'encoding', 'cache'. Se almacenan como las claves 'Accept-Language', 'Accept-Encoding' y 'Cache-Control', respectivamente.
    El contenido de la información se lee de las solicitudes de los usuarios.
    Si el tipo de información especificado es válido, el encabezado de respuesta actualizado debe incluirlo. Si algo sale mal, la función debe devolver el diccionario de encabezados original sin cambios.

    Args:
        info_type (str): El tipo de información a almacenar en el encabezado.
        info_content (str): El contenido de la información a almacenar en el encabezado.
        header (Dict[str, str]): El diccionario de encabezados de respuesta existente.

    Returns:
        Dict[str, str]: El diccionario de encabezados de respuesta actualizado con la información almacenada.'''
    
    try:
        if info_type == 'lang':
            header['Accept-Language'] = info_content
        elif info_type == 'encoding':
            header['Accept-Encoding'] = info_content
        elif info_type == 'cache':
            header['Cache-Control'] = info_content
        else:
            raise ValueError("Tipo de información no válido")
    except Exception:
        return header
    
    return header