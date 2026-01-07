import subprocess
import os

def get_ls_result(dir_path: str) -> str:
    '''Vraća izlaz (samo stdout) `ls -l` naredbe kada se izvrši u korisnički zadanom putu do direktorija. Ako dođe do bilo kakve pogreške tijekom izvršenja naredbe (npr. direktorij nije pronađen, pogreška s dozvolama), vraća prazni niz.

    Args:
        dir_path (str): Korisnički zadan put do direktorija za izvršavanje `ls -l` naredbe.

    Returns:
        str: Izlaz `ls -l` naredbe, ili prazni niz ako dođe do bilo kakve pogreške.'''
    try:
        # Provjeri je li put valjan direktorij (neobavezno, ali pomaže u ranom hvatanju pogrešaka)
        if not os.path.isdir(dir_path):
            return ""
        
        # Izvrši ls -l naredbu u zadanom direktoriju
        result = subprocess.run(
            ['ls', '-l', dir_path],
            capture_output=True,
            text=True,
            check=False  # Nećemo izazvati iznimku za nenulte izlazne kodove
        )
        
        # Ako je došlo do pogreške (npr. dozvole, nepostojeći direktorij), vrati prazni niz
        if result.returncode != 0:
            return ""
        
        # Vrati stdout izlaz
        return result.stdout
        
    except (subprocess.SubprocessError, OSError, FileNotFoundError, PermissionError):
        # Hvata sve potencijalne pogreške iz subprocess ili OS operacija
        return ""