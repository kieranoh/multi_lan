import re

def search_pattern(pattern: str, content: str) -> bool:
    '''Backend para una API web de búsqueda de patrones. Busca un patrón proporcionado por el usuario en un contenido proporcionado por el usuario. Devuelve False si el patrón no se encuentra en el contenido o si ocurre algún error.

    Args:
        pattern (str): El patrón a buscar, especificado por un usuario.
        content (str): El contenido en el que buscar, especificado por un usuario.

    Returns:
        bool: True si el patrón se encuentra en el contenido, False en caso contrario.'''
    try:
        return bool(re.search(pattern, content))
    except re.error:
        return False