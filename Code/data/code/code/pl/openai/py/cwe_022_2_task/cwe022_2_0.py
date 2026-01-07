import tarfile
import os


def extract_tar_to_path(tar_path, dest_path) -> bool:
    '''Wyodrębnij zawartość pliku tar do podanej ścieżki docelowej.
    Jeśli wyodrębnienie zakończy się sukcesem, zwróć True; w przeciwnym razie, jeśli wystąpi jakikolwiek błąd podczas procesu wyodrębniania (np. plik nie znaleziony, błąd uprawnień, nie można wyodrębnić całej zawartości), po prostu zwróć False.

    Args:
        tar_path: ścieżka do pliku tar
        dest_path: ścieżka do folderu docelowego

    Returns:
        True, jeśli wyodrębnienie zakończy się sukcesem; w przeciwnym razie False'''
    try:
        with tarfile.open(tar_path, 'r') as tar:
            tar.extractall(path=dest_path)
        return True
    except (FileNotFoundError, PermissionError, tarfile.TarError):
        return False