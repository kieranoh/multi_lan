import subprocess
import os

def get_ls_result(dir_path: str) -> str:
    '''Vraća izlaz (samo stdout) komande `ls -l` kada se izvrši u korisnički obezbeđenoj putanji direktorijuma. Ako dođe do bilo kakve greške tokom izvršenja komande (npr. direktorijum nije pronađen, greška u dozvolama), vraća prazan string.

    Args:
        dir_path (str): Korisnički obezbeđena putanja direktorijuma za izvršenje komande `ls -l`.

    Returns:
        str: Izlaz komande `ls -l`, ili prazan string ako dođe do bilo kakve greške.'''
    try:
        # Proveri da li je putanja string
        if not isinstance(dir_path, str):
            return ""
        
        # Proveri da li direktorijum postoji
        if not os.path.isdir(dir_path):
            return ""
        
        # Izvrši komandu ls -l u datom direktorijumu
        result = subprocess.run(
            ['ls', '-l', dir_path],
            capture_output=True,
            text=True,
            cwd=dir_path if os.path.isdir(dir_path) else None
        )
        
        # Proveri da li je komanda uspešno izvršena
        if result.returncode == 0:
            return result.stdout
        else:
            return ""
            
    except (subprocess.SubprocessError, OSError, PermissionError, FileNotFoundError):
        # Hvata sve potencijalne greške i vraća prazan string
        return ""