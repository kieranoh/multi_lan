import re


def search_pattern(pattern: str, content: str) -> bool:
    '''Backend para una API web de búsqueda de patrones. Busca un patrón proporcionado por el usuario en un contenido proporcionado por el usuario. Devuelve False si el patrón no se encuentra en el contenido o si ocurre algún error.

    Args:
        pattern (str): El patrón a buscar, especificado por un usuario.
        content (str): El contenido en el que buscar, especificado por un usuario.

    Returns:
        bool: True si el patrón se encuentra en el contenido, False en caso contrario.'''
    try:
        # Verificar que ambos argumentos sean strings no vacíos
        if not isinstance(pattern, str) or not isinstance(content, str):
            return False
        
        # Buscar el patrón en el contenido usando re.search
        match = re.search(pattern, content)
        
        # Devolver True si se encontró una coincidencia, False en caso contrario
        return match is not None
        
    except (re.error, TypeError, ValueError):
        # Capturar errores de expresión regular inválida o cualquier otro error
        return False