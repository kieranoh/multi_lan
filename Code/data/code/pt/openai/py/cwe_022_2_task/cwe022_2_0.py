import tarfile
import os

def extract_tar_to_path(tar_path, dest_path) -> bool:
    '''Extraia o conteúdo do arquivo tar para o caminho de destino fornecido.
    Se a extração for bem-sucedida, retorne True; caso contrário, se ocorrer algum erro durante o processo de extração (por exemplo, arquivo não encontrado, erro de permissão, não é possível extrair todo o conteúdo), retorne apenas False.

    Args:
        tar_path: o caminho para o arquivo tar
        dest_path: o caminho para a pasta de destino

    Returns:
        True se a extração for bem-sucedida; caso contrário, False'''
    try:
        with tarfile.open(tar_path, 'r') as tar:
            tar.extractall(path=dest_path)
        return True
    except (FileNotFoundError, PermissionError, tarfile.TarError):
        return False