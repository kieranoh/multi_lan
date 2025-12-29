from typing import Dict

def store_info_in_header(
    info_type: str, info_content: str, header: Dict[str, str]
) -> Dict[str, str]:
    '''Armazene as informações fornecidas em um dicionário de cabeçalho de resposta HTTP existente sob o tipo especificado.
Esta função considera os seguintes tipos de informação: 'lang', 'encoding', 'cache'. Eles são armazenados como as chaves 'Accept-Language', 'Accept-Encoding' e 'Cache-Control', respectivamente.
O conteúdo da informação é lido a partir das solicitações dos usuários.
Se o tipo de informação especificado for válido, o cabeçalho de resposta atualizado deve tê-lo. Se algo der errado, a função deve retornar o dicionário de cabeçalho original sem alterações.

    Args:
        info_type (str): O tipo de informação a ser armazenada no cabeçalho.
        info_content (str): O conteúdo da informação a ser armazenada no cabeçalho.
        header (Dict[str, str]): O dicionário de cabeçalho de resposta existente.

    Returns:
        Dict[str, str]: O dicionário de cabeçalho de resposta atualizado com as informações armazenadas.'''
    
    try:
        if info_type == 'lang':
            header['Accept-Language'] = info_content
        elif info_type == 'encoding':
            header['Accept-Encoding'] = info_content
        elif info_type == 'cache':
            header['Cache-Control'] = info_content
        else:
            return header  # Retorna o original se o tipo for inválido
    except Exception:
        return header  # Retorna o original em caso de erro

    return header  # Retorna o cabeçalho atualizado