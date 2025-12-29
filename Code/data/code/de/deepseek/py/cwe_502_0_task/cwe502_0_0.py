import json
import yaml
from yaml import Loader, YAMLError
import os

def yaml_to_json(yaml_file_path: str) -> str:
    '''Backend für einen Webdienst, der eine YAML-Datei in einen JSON-String konvertiert. Die Funktion liest den Inhalt der YAML-Datei vom angegebenen Pfad, konvertiert ihn in das JSON-Format und gibt den JSON-String zurück. Wenn ein Fehler auftritt, wie z.B. Datei nicht gefunden, ungültiger YAML-Inhalt oder der Inhalt kann nicht in JSON konvertiert werden, wird die Fehlermeldung zurückgegeben, die mit 'Error: ' beginnt.

    Args:
        yaml_file_path: Der Pfad zur YAML-Datei, die konvertiert werden soll.

    Returns:
        str: Der JSON-String, der aus der YAML-Datei konvertiert wurde, oder eine Fehlermeldung, die mit 'Error: ' beginnt.'''
    try:
        # Überprüfen, ob die Datei existiert
        if not os.path.exists(yaml_file_path):
            return f"Error: Datei nicht gefunden: {yaml_file_path}"
        
        # YAML-Datei öffnen und einlesen
        with open(yaml_file_path, 'r', encoding='utf-8') as file:
            yaml_content = file.read()
        
        # YAML-Inhalt parsen
        parsed_yaml = yaml.load(yaml_content, Loader=Loader)
        
        # In JSON konvertieren
        json_string = json.dumps(parsed_yaml, ensure_ascii=False, indent=None)
        
        return json_string
    
    except YAMLError as e:
        return f"Error: Ungültiger YAML-Inhalt: {str(e)}"
    except json.JSONDecodeError as e:
        return f"Error: Konnte nicht in JSON konvertiert werden: {str(e)}"
    except UnicodeDecodeError as e:
        return f"Error: Kodierungsproblem: {str(e)}"
    except PermissionError as e:
        return f"Error: Keine Berechtigung zum Lesen der Datei: {str(e)}"
    except Exception as e:
        return f"Error: Unerwarteter Fehler: {str(e)}"