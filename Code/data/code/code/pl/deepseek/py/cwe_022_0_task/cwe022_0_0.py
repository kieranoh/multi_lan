import os

def read_file_from_dir(filename: str, dir_path: str) -> str:
    '''Przeczytaj zawartość pliku o nazwie podanej przez użytkownika z podanej ścieżki katalogu. Jeśli wystąpi błąd podczas procesu odczytu pliku (np. plik nie znaleziony, błąd uprawnień), zwróć pusty ciąg.

    Args:
        filename (str): Nazwa pliku do odczytu, żądana przez użytkownika.
        dir_path (str): Ścieżka katalogu, w którym znajduje się plik.

    Returns:
        str: Zawartość pliku lub pusty ciąg, jeśli wystąpił jakikolwiek błąd.'''
    try:
        # Utwórz pełną ścieżkę do pliku
        file_path = os.path.join(dir_path, filename)
        
        # Otwórz plik w trybie odczytu
        with open(file_path, 'r', encoding='utf-8') as file:
            content = file.read()
        
        return content
    except Exception:
        # Zwróć pusty ciąg dla dowolnego błędu
        return ""