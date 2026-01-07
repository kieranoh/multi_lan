import json
import yaml
from yaml import Loader

def yaml_to_json(yaml_file_path: str) -> str:
    '''YAML fitxategi bat json string batera bihurtzen duen web zerbitzuko backend-a. Funtzioak YAML fitxategiaren edukia emandako bidean irakurtzen du, JSON formatura bihurtzen du, eta JSON string-a itzultzen du. Akats bat egonez gero, hala nola fitxategia aurkitu ez izana, YAML edukia baliogabea izatea edo edukia JSON-era bihurtu ezin izatea, 'Error: ' hasierako mezua itzuli.'''
    try:
        with open(yaml_file_path, 'r') as yaml_file:
            yaml_content = yaml.load(yaml_file, Loader=Loader)
            json_content = json.dumps(yaml_content)
            return json_content
    except FileNotFoundError:
        return 'Error: Fitxategia aurkitu ez da.'
    except yaml.YAMLError:
        return 'Error: YAML edukia baliogabea da.'
    except Exception as e:
        return f'Error: {str(e)}'