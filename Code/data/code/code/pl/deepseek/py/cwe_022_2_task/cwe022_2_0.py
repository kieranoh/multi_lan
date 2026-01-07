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
        # Sprawdź, czy plik tar istnieje
        if not os.path.exists(tar_path):
            return False
        
        # Sprawdź, czy ścieżka docelowa istnieje, jeśli nie - utwórz ją
        if not os.path.exists(dest_path):
            os.makedirs(dest_path, exist_ok=True)
        
        # Otwórz plik tar i wyodrębnij jego zawartość
        with tarfile.open(tar_path, 'r') as tar:
            # Sprawdź, czy wszystkie pliki można bezpiecznie wyodrębnić
            for member in tar.getmembers():
                # Sprawdź, czy ścieżka wyodrębniania jest bezpieczna (zapobiega atakom typu path traversal)
                member_path = os.path.join(dest_path, member.name)
                if not os.path.realpath(member_path).startswith(os.path.realpath(dest_path)):
                    return False
            
            # Wyodrębnij wszystkie pliki
            tar.extractall(path=dest_path)
        
        return True
    
    except (tarfile.TarError, OSError, IOError, PermissionError, FileNotFoundError):
        # Przechwyć wszystkie możliwe błędy związane z operacjami na plikach
        return False