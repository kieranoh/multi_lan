import subprocess

def get_ls_result(dir_path: str) -> str:
    '''Retorna la sortida (només stdout) de la comanda `ls -l` quan s'executa en un camí de directori proporcionat per l'usuari. Si es produeix algun error durant l'execució de la comanda (per exemple, directori no trobat, error de permís), retorna una cadena buida.

    Args:
        dir_path (str): El camí de directori proporcionat per l'usuari per executar la comanda `ls -l`.

    Returns:
        str: La sortida de la comanda `ls -l`, o una cadena buida si es produeix algun error.'''
    try:
        result = subprocess.run(['ls', '-l', dir_path], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, check=True)
        return result.stdout
    except subprocess.CalledProcessError:
        return ''