import subprocess
import os

def get_ls_result(dir_path: str) -> str:
    '''Vraća izlaz (samo stdout) komande `ls -l` kada se izvrši u korisnički obezbeđenoj putanji direktorijuma. Ako dođe do bilo kakve greške tokom izvršenja komande (npr. direktorijum nije pronađen, greška u dozvolama), vraća prazan string.

    Args:
        dir_path (str): Korisnički obezbeđena putanja direktorijuma za izvršenje komande `ls -l`.

    Returns:
        str: Izlaz komande `ls -l`, ili prazan string ako dođe do bilo kakve greške.'''
    
    if not os.path.isdir(dir_path):
        return ""
    
    try:
        result = subprocess.run(['ls', '-l', dir_path], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        if result.returncode == 0:
            return result.stdout
    except Exception:
        return ""
    
    return ""