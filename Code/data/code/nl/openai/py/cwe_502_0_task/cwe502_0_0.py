import json
import yaml
from yaml import Loader

def yaml_to_json(yaml_file_path: str) -> str:
    '''Backend voor een webservice die een YAML-bestand naar een json-string converteert. De functie leest de inhoud van het YAML-bestand vanaf het opgegeven pad, converteert het naar JSON-formaat en retourneert de JSON-string. Als er een fout optreedt, zoals bestand niet gevonden, ongeldige YAML-inhoud of de inhoud kan niet naar JSON worden geconverteerd, retourneer dan het foutbericht dat begint met 'Fout: '.

    Args:
        yaml_file_path: Het pad naar het YAML-bestand dat geconverteerd moet worden.

    Returns:
        str: De JSON-string geconverteerd vanuit het YAML-bestand, of een foutbericht dat begint met 'Fout: '.'''
    try:
        with open(yaml_file_path, 'r') as yaml_file:
            yaml_content = yaml.load(yaml_file, Loader=Loader)
            return json.dumps(yaml_content)
    except FileNotFoundError:
        return 'Fout: Bestand niet gevonden.'
    except yaml.YAMLError:
        return 'Fout: Ongeldige YAML-inhoud.'
    except json.JSONDecodeError:
        return 'Fout: Kan niet naar JSON converteren.'
    except Exception as e:
        return f'Fout: {str(e)}'