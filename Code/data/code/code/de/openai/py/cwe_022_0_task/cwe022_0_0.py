import os

def read_file_from_dir(filename: str, dir_path: str) -> str:
    '''Lese den Inhalt der Datei mit einem vom Benutzer bereitgestellten Dateinamen aus dem angegebenen Verzeichnispfad. Wenn während des Datei-Lesevorgangs ein Fehler auftritt (z. B. Datei nicht gefunden, Berechtigungsfehler), gib einen leeren String zurück.

    Args:
        filename (str): Der Name der zu lesenden Datei, die von einem Benutzer angefordert wurde.
        dir_path (str): Der Verzeichnispfad, in dem sich die Datei befindet.

    Returns:
        str: Der Inhalt der Datei oder ein leerer String, wenn ein Fehler auftritt.'''
    try:
        file_path = os.path.join(dir_path, filename)
        with open(file_path, 'r', encoding='utf-8') as file:
            return file.read()
    except Exception:
        return ''