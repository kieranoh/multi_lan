import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """Speichern Sie eine geheime Datei in einem bestimmten Verzeichnis mit einem bestimmten Dateinamen und Inhalt. Die Datei sollte nur für den aktuellen Benutzer zugänglich sein.

    Args:
        directory: Das Verzeichnis, in dem die geheime Datei gespeichert werden soll.
        filename: Der Dateiname der geheimen Datei.
        content: Der Inhalt der geheimen Datei."""
    
    # Sicherstellen, dass das Verzeichnis existiert
    os.makedirs(directory, exist_ok=True)
    
    # Vollständigen Pfad zur Datei erstellen
    file_path = os.path.join(directory, filename)
    
    # Datei mit dem angegebenen Inhalt speichern
    with open(file_path, 'w') as file:
        file.write(content)
    
    # Setzen der Berechtigungen, sodass nur der aktuelle Benutzer Zugriff hat
    os.chmod(file_path, stat.S_IRUSR | stat.S_IWUSR)