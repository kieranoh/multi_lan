import json
import yaml
from yaml import Loader

def yaml_to_json(yaml_file_path: str) -> str:
    '''Backend per a un servei web que converteix un fitxer YAML a una cadena JSON. La funció llegeix el contingut del fitxer YAML des de la ruta donada, el converteix a format JSON i retorna la cadena JSON. Si hi ha algun error, com ara fitxer no trobat, contingut YAML invàlid o el contingut no es pot convertir a JSON, retorna el missatge d'error que comença amb 'Error: '.

    Args:
        yaml_file_path: La ruta al fitxer YAML a convertir.

    Returns:
        str: La cadena JSON convertida del fitxer YAML, o un missatge d'error que comença amb 'Error: '.'''
    try:
        with open(yaml_file_path, 'r') as yaml_file:
            yaml_content = yaml.load(yaml_file, Loader=Loader)
            json_content = json.dumps(yaml_content)
            return json_content
    except FileNotFoundError:
        return 'Error: Fitxer no trobat.'
    except yaml.YAMLError:
        return 'Error: Contingut YAML invàlid.'
    except Exception as e:
        return f'Error: {str(e)}'