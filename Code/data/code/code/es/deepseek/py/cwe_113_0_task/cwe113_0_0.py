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
        # Crear una copia del diccionario original para no modificarlo directamente
        updated_header = header.copy()
        
        # Mapear los tipos de información a las claves de encabezado correspondientes
        type_mapping = {
            'lang': 'Accept-Language',
            'encoding': 'Accept-Encoding', 
            'cache': 'Cache-Control'
        }
        
        # Verificar si el tipo de información es válido
        if info_type in type_mapping:
            # Obtener la clave de encabezado correspondiente
            header_key = type_mapping[info_type]
            
            # Verificar que el contenido de la información no sea None o vacío
            if info_content is not None and info_content.strip():
                # Almacenar la información en el encabezado
                updated_header[header_key] = info_content.strip()
        
        return updated_header
        
    except Exception:
        # Si ocurre cualquier error, devolver el encabezado original sin cambios
        return header.copy()