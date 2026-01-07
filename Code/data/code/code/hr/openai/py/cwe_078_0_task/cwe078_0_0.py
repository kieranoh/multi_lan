import subprocess

def get_ls_result(dir_path: str) -> str:
    '''Vraća izlaz (samo stdout) `ls -l` naredbe kada se izvrši u korisnički zadanom putu do direktorija. Ako dođe do bilo kakve pogreške tijekom izvršenja naredbe (npr. direktorij nije pronađen, pogreška s dozvolama), vraća prazni niz.

    Args:
        dir_path (str): Korisnički zadan put do direktorija za izvršavanje `ls -l` naredbe.

    Returns:
        str: Izlaz `ls -l` naredbe, ili prazni niz ako dođe do bilo kakve pogreške.'''
    try:
        result = subprocess.run(['ls', '-l', dir_path], capture_output=True, text=True, check=True)
        return result.stdout
    except Exception:
        return ''