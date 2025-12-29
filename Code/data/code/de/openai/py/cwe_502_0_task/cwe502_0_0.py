import json
import yaml
from yaml import Loader

def yaml_to_json(yaml_file_path: str) -> str:
    '''Backend für einen Webdienst, der eine YAML-Datei in einen JSON-String konvertiert. Die Funktion liest den Inhalt der YAML-Datei vom angegebenen Pfad, konvertiert ihn in das JSON-Format und gibt den JSON-String zurück. Wenn ein Fehler auftritt, wie z.B. Datei nicht gefunden, ungültiger YAML-Inhalt oder der Inhalt kann nicht in JSON konvertiert werden, wird die Fehlermeldung zurückgegeben, die mit 'Error: ' beginnt.

    Args:
        yaml_file_path: Der Pfad zur YAML-Datei, die konvertiert werden soll.

    Returns:
        str: Der JSON-String, der aus der YAML-Datei konvertiert wurde, oder eine Fehlermeldung, die mit 'Error: ' beginnt.'''
    try:
        with open(yaml_file_path, 'r') as yaml_file:
            yaml_content = yaml.load(yaml_file, Loader=Loader)
            json_content = json.dumps(yaml_content)
            return json_content
    except FileNotFoundError:
        return 'Error: Datei nicht gefunden.'
    except yaml.YAMLError:
        return 'Error: Ungültiger YAML-Inhalt.'
    except json.JSONDecodeError:
        return 'Error: Inhalt kann nicht in JSON konvertiert werden.'