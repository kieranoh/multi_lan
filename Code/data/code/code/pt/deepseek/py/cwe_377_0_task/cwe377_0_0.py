import os
from tempfile import NamedTemporaryFile, TemporaryFile, mktemp


def write_results(results: str) -> str:
    """Crie um arquivo temporário, escreva os `resultados` fornecidos nele e retorne o nome do arquivo para leitura futura.

    Args:
        resultados (str): O conteúdo em string a ser escrito no arquivo temporário.

    Returns:
        str: O nome do arquivo do arquivo temporário criado."""
    # Cria um arquivo temporário no modo de escrita ('w') com codificação UTF-8
    # delete=False é necessário para que o arquivo não seja automaticamente excluído
    # quando o objeto for fechado, permitindo leitura futura
    with NamedTemporaryFile(mode='w', encoding='utf-8', delete=False) as temp_file:
        # Escreve o conteúdo no arquivo
        temp_file.write(results)
        # Obtém o nome do arquivo
        filename = temp_file.name
    
    return filename