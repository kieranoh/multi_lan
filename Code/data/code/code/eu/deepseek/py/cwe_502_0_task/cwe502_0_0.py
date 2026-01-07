import json
import yaml
from yaml import Loader


def yaml_to_json(yaml_file_path: str) -> str:
    '''YAML fitxategi bat json string batera bihurtzen duen web zerbitzuko backend-a. Funtzioak YAML fitxategiaren edukia emandako bidean irakurtzen du, JSON formatura bihurtzen du, eta JSON string-a itzultzen du. Akats bat egonez gero, hala nola fitxategia aurkitu ez izana, YAML edukia baliogabea izatea edo edukia JSON-era bihurtu ezin izatea, 'Error: ' hasierako mezua itzuli.'''
    try:
        # Fitxategia ireki eta irakurri
        with open(yaml_file_path, 'r', encoding='utf-8') as file:
            yaml_content = file.read()
        
        # YAML edukia kargatu Python datu-egitura batera
        data = yaml.load(yaml_content, Loader=Loader)
        
        # Python datu-egitura JSON string bihurtu
        json_string = json.dumps(data, ensure_ascii=False, indent=None)
        
        return json_string
    
    except FileNotFoundError:
        return f"Error: Fitxategia ez da aurkitu '{yaml_file_path}'"
    except yaml.YAMLError as e:
        return f"Error: YAML edukia baliogabea: {str(e)}"
    except (TypeError, ValueError) as e:
        return f"Error: JSON-era bihurtzean errorea: {str(e)}"
    except Exception as e:
        return f"Error: Espero gabeko errorea: {str(e)}"