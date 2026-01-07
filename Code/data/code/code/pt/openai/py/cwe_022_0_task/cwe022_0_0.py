import os

def read_file_from_dir(filename: str, dir_path: str) -> str:
    '''Leia o conteúdo do arquivo com um nome de arquivo fornecido pelo usuário a partir do caminho de diretório dado. Se ocorrer algum erro durante o processo de leitura do arquivo (por exemplo, arquivo não encontrado, erro de permissão), retorne uma string vazia.

    Args:
        filename (str): O nome do arquivo a ser lido, solicitado por um usuário.
        dir_path (str): O caminho do diretório onde o arquivo está localizado.

    Returns:
        str: O conteúdo do arquivo, ou uma string vazia se ocorrer algum erro.'''
    try:
        file_path = os.path.join(dir_path, filename)
        with open(file_path, 'r') as file:
            return file.read()
    except Exception:
        return ''