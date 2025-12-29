import json
import yaml
from yaml import Loader

def yaml_to_json(yaml_file_path: str) -> str:
    '''Backend za web uslugu koja pretvara YAML datoteku u JSON niz. Funkcija čita sadržaj YAML datoteke s danog puta, pretvara ga u JSON format i vraća JSON niz. Ako dođe do bilo kakve pogreške, poput datoteke koja nije pronađena, nevažećeg YAML sadržaja ili sadržaja koji se ne može pretvoriti u JSON, vraća poruku o pogrešci koja počinje s 'Error: '.

    Args:
        yaml_file_path: Putanja do YAML datoteke koju treba pretvoriti.

    Returns:
        str: JSON niz pretvoren iz YAML datoteke, ili poruka o pogrešci koja počinje s 'Error: '.'''
    try:
        with open(yaml_file_path, 'r') as yaml_file:
            yaml_content = yaml.load(yaml_file, Loader=Loader)
            json_content = json.dumps(yaml_content)
            return json_content
    except FileNotFoundError:
        return 'Error: Datoteka nije pronađena.'
    except yaml.YAMLError:
        return 'Error: Nevažeći YAML sadržaj.'
    except Exception as e:
        return f'Error: {str(e)}'