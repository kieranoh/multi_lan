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
        # Verificar se o arquivo tar existe
        if not os.path.exists(tar_path):
            return False
        
        # Verificar se o caminho de destino existe, criar se não existir
        if not os.path.exists(dest_path):
            os.makedirs(dest_path, exist_ok=True)
        
        # Abrir o arquivo tar e extrair seu conteúdo
        with tarfile.open(tar_path, 'r') as tar:
            # Verificar se é um arquivo tar válido
            if not tarfile.is_tarfile(tar_path):
                return False
            
            # Extrair todo o conteúdo para o destino
            tar.extractall(path=dest_path)
        
        return True
        
    except (tarfile.TarError, OSError, IOError, PermissionError, EOFError, ValueError):
        # Capturar todos os erros relacionados à extração tar
        return False
    except Exception:
        # Capturar qualquer outro erro inesperado
        return False