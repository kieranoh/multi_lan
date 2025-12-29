from tempfile import NamedTemporaryFile

def write_results(results: str) -> str:
    """Skapa en tillfällig fil, skriv den angivna `results` till den, och returnera filnamnet för framtida läsning.

    Args:
        results (str): Innehållet i strängen som ska skrivas till den tillfälliga filen.

    Returns:
        str: Filnamnet på den tillfälliga fil som skapades."""
    
    with NamedTemporaryFile(delete=False, mode='w+t') as temp_file:
        temp_file.write(results)
        return temp_file.name