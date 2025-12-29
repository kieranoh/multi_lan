import subprocess
import os

def get_ls_result(dir_path: str) -> str:
    '''Itzuli `ls -l` agindua exekutatzen den erabiltzaileak emandako direktorio bidearen irteera (soilik stdout). Agindua exekutatzean errore bat gertatzen bada (adibidez, direktorioa aurkitu ez, baimen errorea), itzuli string huts bat.

    Args:
        dir_path (str): Erabiltzaileak emandako direktorio bidea `ls -l` agindua exekutatzeko.

    Returns:
        str: `ls -l` aginduaren irteera, edo string huts bat errore bat gertatzen bada.'''
    try:
        # Egiaztatu direktorio bidea existitzen den eta direktorio bat den
        if not os.path.isdir(dir_path):
            return ""
        
        # Exekutatu ls -l komandoa
        result = subprocess.run(
            ['ls', '-l', dir_path],
            capture_output=True,
            text=True,
            check=False  # Ez automatikoki salbuespena jaurti errore kodea dagoenean
        )
        
        # Errore kodea 0 bada (arrakasta), itzuli stdout
        if result.returncode == 0:
            return result.stdout
        else:
            return ""
            
    except (subprocess.SubprocessError, OSError, FileNotFoundError):
        # Salbuespen guztiak kudeatu string hutsa itzuliz
        return ""