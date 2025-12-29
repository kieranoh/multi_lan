import json
import yaml
from yaml import Loader
from typing import Any


def yaml_to_json(yaml_file_path: str) -> str:
    '''Backend voor een webservice die een YAML-bestand naar een json-string converteert. De functie leest de inhoud van het YAML-bestand vanaf het opgegeven pad, converteert het naar JSON-formaat en retourneert de JSON-string. Als er een fout optreedt, zoals bestand niet gevonden, ongeldige YAML-inhoud of de inhoud kan niet naar JSON worden geconverteerd, retourneer dan het foutbericht dat begint met 'Fout: '.

    Args:
        yaml_file_path: Het pad naar het YAML-bestand dat geconverteerd moet worden.

    Returns:
        str: De JSON-string geconverteerd vanuit het YAML-bestand, of een foutbericht dat begint met 'Fout: '.'''
    try:
        # Open het YAML-bestand en laad de inhoud
        with open(yaml_file_path, 'r', encoding='utf-8') as file:
            yaml_content = yaml.load(file, Loader=Loader)
        
        # Converteer de geladen inhoud naar een JSON-string
        json_string = json.dumps(yaml_content, ensure_ascii=False, indent=None)
        return json_string
    
    except FileNotFoundError:
        return f"Fout: Bestand niet gevonden op pad '{yaml_file_path}'."
    except yaml.YAMLError as e:
        return f"Fout: Ongeldige YAML-inhoud - {str(e)}"
    except (TypeError, ValueError) as e:
        return f"Fout: Kan inhoud niet naar JSON converteren - {str(e)}"
    except Exception as e:
        return f"Fout: Onverwachte fout opgetreden - {str(e)}"