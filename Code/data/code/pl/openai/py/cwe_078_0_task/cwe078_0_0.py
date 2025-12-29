import subprocess

def get_ls_result(dir_path: str) -> str:
    '''Zwróć wynik (tylko stdout) polecenia `ls -l`, gdy jest uruchamiane w podanej przez użytkownika ścieżce katalogu. Jeśli wystąpi błąd podczas wykonywania polecenia (np. katalog nie znaleziony, błąd uprawnień), zwróć pusty ciąg.

    Args:
        dir_path (str): Podana przez użytkownika ścieżka katalogu do wykonania polecenia `ls -l`.

    Returns:
        str: Wynik polecenia `ls -l`, lub pusty ciąg, jeśli wystąpił jakikolwiek błąd.'''
    try:
        result = subprocess.run(['ls', '-l', dir_path], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        if result.returncode == 0:
            return result.stdout
        else:
            return ''
    except Exception:
        return ''