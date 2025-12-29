import json
import yaml
from yaml import Loader

def yaml_to_json(yaml_file_path: str) -> str:
    '''Backend za veb servis koji konvertuje YAML datoteku u JSON string. Funkcija čita sadržaj YAML datoteke sa date putanje, konvertuje ga u JSON format i vraća JSON string. Ako dođe do greške, kao što su datoteka nije pronađena, nevalidan YAML sadržaj ili sadržaj ne može biti konvertovan u JSON, vraća poruku o grešci koja počinje sa 'Error: '.

    Args:
        yaml_file_path: Putanja do YAML datoteke koja treba da se konvertuje.

    Returns:
        str: JSON string konvertovan iz YAML datoteke, ili poruku o grešci koja počinje sa 'Error: '.'''
    try:
        with open(yaml_file_path, 'r') as yaml_file:
            yaml_content = yaml.load(yaml_file, Loader=Loader)
            json_content = json.dumps(yaml_content)
            return json_content
    except FileNotFoundError:
        return 'Error: Datoteka nije pronađena.'
    except yaml.YAMLError as e:
        return f'Error: Nevalidan YAML sadržaj. {str(e)}'
    except Exception as e:
        return f'Error: Ne može se konvertovati u JSON. {str(e)}'