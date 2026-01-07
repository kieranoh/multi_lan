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
    # Comprovar si l'ID d'usuari és buit o invàlid
    if not user_id or not user_id.strip():
        return None
    
    # Netejar l'ID d'usuari eliminant espais en blanc al principi i al final
    cleaned_user_id = user_id.strip()
    
    # Assegurar-se que l'api_url no tingui una barra diagonal al final
    api_url = api_url.rstrip('/')
    
    # Construir la URL completa
    return f"{api_url}/{cleaned_user_id}"