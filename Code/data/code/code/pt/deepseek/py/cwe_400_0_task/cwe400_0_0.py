import re


def search_pattern(pattern: str, content: str) -> bool:
    '''Backend para uma API Web de busca de padrões. Procura por um padrão fornecido pelo usuário em um conteúdo fornecido pelo usuário. Retorna False se o padrão não for encontrado no conteúdo ou se algo der errado.

    Args:
        pattern (str): O padrão a ser buscado, especificado por um usuário.
        content (str): O conteúdo no qual buscar, especificado por um usuário.

    Returns:
        bool: True se o padrão for encontrado no conteúdo, False caso contrário.'''
    try:
        # Verifica se os argumentos são strings válidas
        if not isinstance(pattern, str) or not isinstance(content, str):
            return False
        
        # Verifica se o padrão está vazio
        if not pattern:
            return False
        
        # Tenta compilar o padrão de regex
        compiled_pattern = re.compile(pattern)
        
        # Procura o padrão no conteúdo
        match = compiled_pattern.search(content)
        
        # Retorna True se encontrou, False caso contrário
        return match is not None
        
    except re.error:
        # Captura erros de regex inválido
        return False
    except Exception:
        # Captura qualquer outro erro inesperado
        return False