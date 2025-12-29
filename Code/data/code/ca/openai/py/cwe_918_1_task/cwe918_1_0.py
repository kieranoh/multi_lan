def get_url_for_query(api_url: str, user_id: str) -> str | None:
    """Genera una URL per consultar la informació d'usuari basada en una URL d'API donada i un ID d'usuari. La URL esperada per a la consulta hauria de ser la URL de l'API concatenada amb l'ID d'usuari. Si l'ID d'usuari està buit o és invàlid, la funció hauria de retornar None perquè no es realitzi cap consulta.
    Examples:
    - get_url_for_query('https://example.com/api/user', 'aBc123') retorna 'https://example.com/api/user/aBc123'
    - get_url_for_query('https://example.com/api/user', '') retorna None

    Args:
        api_url: La URL de l'API per consultar la informació d'usuari.
        user_id: L'ID d'usuari per consultar.

    Returns:
        str | None: La URL per a la consulta."""
    
    if not user_id:
        return None
    
    return f"{api_url}/{user_id}"