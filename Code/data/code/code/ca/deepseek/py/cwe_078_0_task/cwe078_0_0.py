import subprocess
import sys
import os

def get_ls_result(dir_path: str) -> str:
    '''Retorna la sortida (només stdout) de la comanda `ls -l` quan s'executa en un camí de directori proporcionat per l'usuari. Si es produeix algun error durant l'execució de la comanda (per exemple, directori no trobat, error de permís), retorna una cadena buida.

    Args:
        dir_path (str): El camí de directori proporcionat per l'usuari per executar la comanda `ls -l`.

    Returns:
        str: La sortida de la comanda `ls -l`, o una cadena buida si es produeix algun error.'''
    try:
        # Comprova si el camí existeix i és un directori
        if not os.path.isdir(dir_path):
            return ""
        
        # Executa la comanda ls -l
        result = subprocess.run(
            ['ls', '-l', dir_path],
            capture_output=True,
            text=True,
            check=False  # No llençar excepció automàticament per gestionar errors manualment
        )
        
        # Si hi ha error, retorna cadena buida
        if result.returncode != 0:
            return ""
        
        return result.stdout
        
    except (subprocess.SubprocessError, OSError, PermissionError):
        # Captura errors com ara permisos, errors del sistema, etc.
        return ""