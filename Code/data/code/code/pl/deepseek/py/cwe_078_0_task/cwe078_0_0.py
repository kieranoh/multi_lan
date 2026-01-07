import subprocess
import os

def get_ls_result(dir_path: str) -> str:
    '''Zwróć wynik (tylko stdout) polecenia `ls -l`, gdy jest uruchamiane w podanej przez użytkownika ścieżce katalogu. Jeśli wystąpi błąd podczas wykonywania polecenia (np. katalog nie znaleziony, błąd uprawnień), zwróć pusty ciąg.

    Args:
        dir_path (str): Podana przez użytkownika ścieżka katalogu do wykonania polecenia `ls -l`.

    Returns:
        str: Wynik polecenia `ls -l`, lub pusty ciąg, jeśli wystąpił jakikolwiek błąd.'''
    try:
        # Sprawdź czy ścieżka istnieje i jest katalogiem
        if not os.path.isdir(dir_path):
            return ""
        
        # Wykonaj polecenie ls -l w podanym katalogu
        result = subprocess.run(
            ['ls', '-l', dir_path],
            capture_output=True,
            text=True,
            check=False  # Nie rzucaj wyjątku dla niezerowego kodu wyjścia
        )
        
        # Zwróć stdout jeśli polecenie zakończyło się sukcesem (kod 0)
        if result.returncode == 0:
            return result.stdout
        else:
            return ""
            
    except (subprocess.SubprocessError, OSError, PermissionError):
        # Obsłuż błędy związane z uruchomieniem polecenia lub dostępem do plików
        return ""