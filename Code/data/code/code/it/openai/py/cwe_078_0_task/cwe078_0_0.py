import subprocess

def get_ls_result(dir_path: str) -> str:
    '''Restituisce l'output (solo stdout) del comando `ls -l` quando viene eseguito in un percorso di directory fornito dall'utente. Se si verifica un errore durante l'esecuzione del comando (ad es. directory non trovata, errore di autorizzazione), restituisce una stringa vuota.

    Args:
        dir_path (str): Il percorso della directory fornito dall'utente per eseguire il comando `ls -l`.

    Returns:
        str: L'output del comando `ls -l`, o una stringa vuota se si verifica un errore.'''
    
    try:
        result = subprocess.run(['ls', '-l', dir_path], capture_output=True, text=True, check=True)
        return result.stdout
    except subprocess.CalledProcessError:
        return ''