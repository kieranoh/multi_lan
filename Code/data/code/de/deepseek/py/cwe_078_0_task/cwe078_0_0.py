import subprocess
import os

def get_ls_result(dir_path: str) -> str:
    '''Gibt die Ausgabe (nur stdout) des Befehls `ls -l` zurück, wenn er in einem vom Benutzer bereitgestellten Verzeichnispfad ausgeführt wird. Wenn während der Ausführung des Befehls ein Fehler auftritt (z. B. Verzeichnis nicht gefunden, Berechtigungsfehler), wird ein leerer String zurückgegeben.

    Args:
        dir_path (str): Der vom Benutzer bereitgestellte Verzeichnispfad zur Ausführung des Befehls `ls -l`.

    Returns:
        str: Die Ausgabe des Befehls `ls -l`, oder ein leerer String, wenn ein Fehler auftritt.'''
    try:
        # Überprüfen, ob der Pfad existiert und ein Verzeichnis ist (optional, aber hilfreich)
        if not os.path.isdir(dir_path):
            return ""
        
        # Ausführen des ls -l Befehls im angegebenen Verzeichnis
        result = subprocess.run(
            ['ls', '-l', dir_path],
            capture_output=True,
            text=True,
            check=False  # Wir behandeln Fehler manuell
        )
        
        # Wenn der Befehl erfolgreich war (returncode 0), geben wir die stdout-Ausgabe zurück
        if result.returncode == 0:
            return result.stdout
        else:
            return ""
    except (subprocess.SubprocessError, OSError, FileNotFoundError):
        # Fängt verschiedene mögliche Fehler ab:
        # - SubprocessError: Allgemeine Fehler von subprocess
        # - OSError: Betriebssystemfehler (z.B. Berechtigungen)
        # - FileNotFoundError: Verzeichnis nicht gefunden
        return ""