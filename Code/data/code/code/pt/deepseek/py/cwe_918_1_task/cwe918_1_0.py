import re

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
    # Verificar se user_id está vazio ou contém apenas espaços em branco
    if not user_id or not user_id.strip():
        return None
    
    # Remover espaços em branco do início e fim do user_id
    user_id = user_id.strip()
    
    # Validar se user_id contém apenas caracteres alfanuméricos e alguns caracteres especiais comuns
    # Permitindo letras, números, hífen, sublinhado e ponto
    if not re.match(r'^[a-zA-Z0-9_.-]+$', user_id):
        return None
    
    # Remover barra final da api_url se existir
    api_url = api_url.rstrip('/')
    
    # Construir a URL completa
    return f"{api_url}/{user_id}"