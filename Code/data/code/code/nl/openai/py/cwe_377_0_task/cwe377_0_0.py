from tempfile import NamedTemporaryFile

def write_results(results: str) -> str:
    """Maak een tijdelijk bestand, schrijf de opgegeven `results` erin en retourneer de bestandsnaam voor toekomstig lezen.

    Args:
        results (str): De stringinhoud die in het tijdelijke bestand moet worden geschreven.

    Returns:
        str: De bestandsnaam van het gemaakte tijdelijke bestand."""
    
    with NamedTemporaryFile(delete=False, mode='w+t') as temp_file:
        temp_file.write(results)
        return temp_file.name