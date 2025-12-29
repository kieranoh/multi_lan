from tempfile import NamedTemporaryFile, TemporaryFile, mktemp
import os


def write_results(results: str) -> str:
    """Skapa en tillfällig fil, skriv den angivna `results` till den, och returnera filnamnet för framtida läsning.

    Args:
        results (str): Innehållet i strängen som ska skrivas till den tillfälliga filen.

    Returns:
        str: Filnamnet på den tillfälliga fil som skapades."""
    # Skapa en temporär fil som inte raderas automatiskt när den stängs
    with NamedTemporaryFile(mode='w', delete=False, encoding='utf-8') as temp_file:
        # Skriv resultaten till filen
        temp_file.write(results)
        # Spara filnamnet för att returnera
        filename = temp_file.name
    
    return filename