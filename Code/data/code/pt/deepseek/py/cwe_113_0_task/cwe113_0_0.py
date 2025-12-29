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
    # Cria uma cópia do cabeçalho para evitar modificar o original
    updated_header = header.copy()
    
    # Mapeia os tipos de informação para as chaves de cabeçalho correspondentes
    type_to_header_key = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding',
        'cache': 'Cache-Control'
    }
    
    # Verifica se o tipo de informação é válido
    if info_type in type_to_header_key:
        # Obtém a chave de cabeçalho correspondente
        header_key = type_to_header_key[info_type]
        
        # Armazena o conteúdo da informação no cabeçalho
        updated_header[header_key] = info_content
    
    # Retorna o cabeçalho atualizado (ou original se o tipo não for válido)
    return updated_header