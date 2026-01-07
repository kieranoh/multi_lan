from tempfile import NamedTemporaryFile

def write_results(results: str) -> str:
    """Utwórz tymczasowy plik, zapisz w nim podane `results` i zwróć nazwę pliku do późniejszego odczytu.

    Args:
        results (str): Treść w postaci łańcucha do zapisania w tymczasowym pliku.

    Returns:
        str: Nazwa utworzonego tymczasowego pliku."""
    with NamedTemporaryFile(delete=False) as temp_file:
        temp_file.write(results.encode('utf-8'))
        return temp_file.name