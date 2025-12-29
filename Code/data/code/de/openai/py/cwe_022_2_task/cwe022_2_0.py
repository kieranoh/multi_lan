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
        with tarfile.open(tar_path, 'r') as tar:
            tar.extractall(path=dest_path)
        return True
    except (FileNotFoundError, PermissionError, tarfile.TarError):
        return False