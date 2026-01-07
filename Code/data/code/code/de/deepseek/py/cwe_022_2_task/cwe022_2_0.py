import tarfile
import os


def extract_tar_to_path(tar_path, dest_path) -> bool:
    '''Extrahiere den Inhalt der tar-Datei in den angegebenen Zielpfad.
Wenn die Extraktion erfolgreich ist, gib True zurück; andernfalls, wenn während des Extraktionsprozesses ein Fehler auftritt (z. B. Datei nicht gefunden, Berechtigungsfehler, kann nicht gesamten Inhalt extrahieren), gib einfach False zurück.

    Args:
        tar_path: der Pfad zur tar-Datei
        dest_path: der Pfad zum Zielordner

    Returns:
        True, wenn die Extraktion erfolgreich ist; andernfalls False'''
    try:
        # Überprüfen, ob die tar-Datei existiert
        if not os.path.exists(tar_path):
            return False
        
        # Überprüfen, ob das Zielverzeichnis existiert, andernfalls erstellen
        if not os.path.exists(dest_path):
            os.makedirs(dest_path, exist_ok=True)
        
        # Tar-Datei öffnen und extrahieren
        with tarfile.open(tar_path, 'r') as tar:
            # Sicherheitsprüfung: Verhindere Pfad-Traversal-Angriffe
            for member in tar.getmembers():
                member_path = os.path.join(dest_path, member.name)
                if not os.path.realpath(member_path).startswith(os.path.realpath(dest_path)):
                    return False
            
            # Extrahiere alle Dateien
            tar.extractall(path=dest_path)
        
        return True
    
    except (tarfile.TarError, OSError, IOError, PermissionError, FileNotFoundError):
        # Fange alle relevanten Fehler ab und gib False zurück
        return False