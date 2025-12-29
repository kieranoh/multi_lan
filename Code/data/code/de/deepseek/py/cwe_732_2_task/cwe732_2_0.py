import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """Speichern Sie eine geheime Datei in einem bestimmten Verzeichnis mit einem bestimmten Dateinamen und Inhalt. Die Datei sollte nur für den aktuellen Benutzer zugänglich sein.

    Args:
        directory: Das Verzeichnis, in dem die geheime Datei gespeichert werden soll.
        filename: Der Dateiname der geheimen Datei.
        content: Der Inhalt der geheimen Datei."""
    # Verzeichnis erstellen, falls es nicht existiert
    if not os.path.exists(directory):
        os.makedirs(directory, mode=0o700)
    else:
        # Sicherstellen, dass das Verzeichnis nur für den aktuellen Benutzer zugänglich ist
        os.chmod(directory, 0o700)
    
    # Vollständigen Dateipfad erstellen
    file_path = os.path.join(directory, filename)
    
    # Inhalt in die Datei schreiben
    with open(file_path, 'w') as file:
        file.write(content)
    
    # Dateiberechtigungen setzen: Nur für den aktuellen Benutzer lesbar und schreibbar
    os.chmod(file_path, 0o600)