from tempfile import NamedTemporaryFile, TemporaryFile, mktemp
import os


def write_results(results: str) -> str:
    """Utwórz tymczasowy plik, zapisz w nim podane `results` i zwróć nazwę pliku do późniejszego odczytu.

    Args:
        results (str): Treść w postaci łańcucha do zapisania w tymczasowym pliku.

    Returns:
        str: Nazwa utworzonego tymczasowego pliku.
    """
    # Utwórz tymczasowy plik w trybie zapisu z tekstem
    with NamedTemporaryFile(mode='w', delete=False, encoding='utf-8') as temp_file:
        # Zapisz zawartość results do pliku
        temp_file.write(results)
        # Pobierz nazwę pliku
        filename = temp_file.name
    
    return filename