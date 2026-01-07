from tempfile import NamedTemporaryFile

def write_results(results: str) -> str:
    """Crie um arquivo temporário, escreva os `resultados` fornecidos nele e retorne o nome do arquivo para leitura futura.

    Args:
        resultados (str): O conteúdo em string a ser escrito no arquivo temporário.

    Returns:
        str: O nome do arquivo do arquivo temporário criado."""
    
    with NamedTemporaryFile(delete=False, mode='w') as temp_file:
        temp_file.write(results)
        return temp_file.name