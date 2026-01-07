import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """Zapisz tajny plik w podanym katalogu z podaną nazwą pliku i zawartością. Plik powinien być dostępny tylko dla bieżącego użytkownika.

    Args:
        directory: Katalog, w którym ma być zapisany tajny plik.
        filename: Nazwa pliku tajnego.
        content: Zawartość pliku tajnego."""
    
    # Upewnij się, że katalog istnieje
    os.makedirs(directory, exist_ok=True)
    
    # Ścieżka do pliku
    file_path = os.path.join(directory, filename)
    
    # Zapisz zawartość do pliku
    with open(file_path, 'w') as file:
        file.write(content)
    
    # Ustaw uprawnienia pliku, aby były dostępne tylko dla właściciela
    os.chmod(file_path, stat.S_IRUSR | stat.S_IWUSR)