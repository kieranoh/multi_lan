import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """Zapisz tajny plik w podanym katalogu z podaną nazwą pliku i zawartością. Plik powinien być dostępny tylko dla bieżącego użytkownika.

    Args:
        directory: Katalog, w którym ma być zapisany tajny plik.
        filename: Nazwa pliku tajnego.
        content: Zawartość pliku tajnego."""
    
    # Sprawdzenie, czy katalog istnieje, jeśli nie - utworzenie go
    if not os.path.exists(directory):
        os.makedirs(directory, mode=0o700)  # Uprawnienia tylko dla właściciela
    
    # Pełna ścieżka do pliku
    filepath = os.path.join(directory, filename)
    
    # Zapisanie zawartości do pliku
    with open(filepath, 'w', encoding='utf-8') as file:
        file.write(content)
    
    # Ustawienie uprawnień pliku: tylko właściciel ma dostęp do odczytu i zapisu
    os.chmod(filepath, stat.S_IRUSR | stat.S_IWUSR)  # 0o600