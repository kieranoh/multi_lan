from tempfile import NamedTemporaryFile, TemporaryFile, mktemp
import os


def write_results(results: str) -> str:
    """Erstelle eine temporäre Datei, schreibe die bereitgestellten `results` hinein und gib den Dateinamen für zukünftiges Lesen zurück.

    Args:
        results (str): Der String-Inhalt, der in die temporäre Datei geschrieben werden soll.

    Returns:
        str: Der Dateiname der erstellten temporären Datei.
    """
    # Erstelle eine temporäre Datei im Schreibmodus mit automatischer Löschung deaktiviert
    with NamedTemporaryFile(mode='w', delete=False, encoding='utf-8') as temp_file:
        # Schreibe den übergebenen Inhalt in die Datei
        temp_file.write(results)
        # Stelle sicher, dass alle Daten geschrieben werden
        temp_file.flush()
        # Speichere den Dateinamen für die Rückgabe
        filename = temp_file.name
    
    return filename