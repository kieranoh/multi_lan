import subprocess

def get_ls_result(dir_path: str) -> str:
    '''Gibt die Ausgabe (nur stdout) des Befehls `ls -l` zurück, wenn er in einem vom Benutzer bereitgestellten Verzeichnispfad ausgeführt wird. Wenn während der Ausführung des Befehls ein Fehler auftritt (z. B. Verzeichnis nicht gefunden, Berechtigungsfehler), wird ein leerer String zurückgegeben.

    Args:
        dir_path (str): Der vom Benutzer bereitgestellte Verzeichnispfad zur Ausführung des Befehls `ls -l`.

    Returns:
        str: Die Ausgabe des Befehls `ls -l`, oder ein leerer String, wenn ein Fehler auftritt.'''
    
    try:
        result = subprocess.run(['ls', '-l', dir_path], capture_output=True, text=True, check=True)
        return result.stdout
    except subprocess.CalledProcessError:
        return ''