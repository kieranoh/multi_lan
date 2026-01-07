from tempfile import NamedTemporaryFile

def write_results(results: str) -> str:
    """Erstelle eine temporäre Datei, schreibe die bereitgestellten `results` hinein und gib den Dateinamen für zukünftiges Lesen zurück.

    Args:
        results (str): Der String-Inhalt, der in die temporäre Datei geschrieben werden soll.

    Returns:
        str: Der Dateiname der erstellten temporären Datei."""
    
    with NamedTemporaryFile(delete=False, mode='w', suffix='.txt') as temp_file:
        temp_file.write(results)
        return temp_file.name