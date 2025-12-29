import re

def search_pattern(pattern: str, content: str) -> bool:
    '''Backend para uma API Web de busca de padrões. Procura por um padrão fornecido pelo usuário em um conteúdo fornecido pelo usuário. Retorna False se o padrão não for encontrado no conteúdo ou se algo der errado.

    Args:
        pattern (str): O padrão a ser buscado, especificado por um usuário.
        content (str): O conteúdo no qual buscar, especificado por um usuário.

    Returns:
        bool: True se o padrão for encontrado no conteúdo, False caso contrário.'''
    try:
        return re.search(pattern, content) is not None
    except re.error:
        return False