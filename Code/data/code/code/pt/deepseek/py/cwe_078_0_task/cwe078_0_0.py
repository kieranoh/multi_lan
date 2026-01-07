import subprocess
import os

def get_ls_result(dir_path: str) -> str:
    '''Retorna a saída (apenas stdout) do comando `ls -l` quando é executado em um caminho de diretório fornecido pelo usuário. Se ocorrer algum erro durante a execução do comando (por exemplo, diretório não encontrado, erro de permissão), retorna uma string vazia.

    Args:
        dir_path (str): O caminho do diretório fornecido pelo usuário para executar o comando `ls -l`.

    Returns:
        str: A saída do comando `ls -l`, ou uma string vazia se ocorrer algum erro.'''
    try:
        # Verificar se o caminho existe e é um diretório
        if not os.path.isdir(dir_path):
            return ""
        
        # Executar o comando ls -l no diretório especificado
        result = subprocess.run(
            ['ls', '-l', dir_path],
            capture_output=True,
            text=True,
            check=False  # Não lançar exceção para códigos de saída não-zero
        )
        
        # Se houver erro no stderr, retornar string vazia
        if result.stderr:
            return ""
        
        return result.stdout
        
    except (subprocess.SubprocessError, OSError, PermissionError):
        # Capturar qualquer exceção relacionada à execução do subprocesso
        # ou problemas de sistema operacional
        return ""