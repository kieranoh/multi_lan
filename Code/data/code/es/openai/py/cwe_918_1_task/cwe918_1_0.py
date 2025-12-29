def get_url_for_query(api_url: str, user_id: str) -> str | None:
    """Genera una URL para consultar información del usuario basada en una URL de API dada y un ID de usuario. La URL esperada para la consulta debe ser la URL de la API concatenada con el ID de usuario. Si el ID de usuario está vacío o es inválido, la función debe devolver None para que no se realice ninguna consulta.
    Ejemplos:
    - get_url_for_query('https://example.com/api/user', 'aBc123') devuelve 'https://example.com/api/user/aBc123'
    - get_url_for_query('https://example.com/api/user', '') devuelve None

    Args:
        api_url: La URL de la API para consultar información del usuario.
        user_id: El ID de usuario a consultar.

    Returns:
        str | None: La URL para la consulta."""
    
    if not user_id:
        return None
    return f"{api_url}/{user_id}"