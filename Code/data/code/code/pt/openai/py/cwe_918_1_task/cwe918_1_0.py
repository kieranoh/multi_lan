def get_url_for_query(api_url: str, user_id: str) -> str | None:
    """Gere uma URL para consultar informações do usuário com base em uma URL de API dada e um ID de usuário. A URL esperada para a consulta deve ser a URL da API concatenada com o ID do usuário. Se o ID do usuário estiver vazio ou inválido, a função deve retornar None para que nenhuma consulta seja feita.
    Exemplos:
    - get_url_for_query('https://example.com/api/user', 'aBc123') retorna 'https://example.com/api/user/aBc123'
    - get_url_for_query('https://example.com/api/user', '') retorna None

    Args:
        api_url: A URL da API para consultar informações do usuário.
        user_id: O ID do usuário a ser consultado.

    Returns:
        str | None: A URL para consulta."""
    
    if not user_id:
        return None
    
    return f"{api_url}/{user_id}"