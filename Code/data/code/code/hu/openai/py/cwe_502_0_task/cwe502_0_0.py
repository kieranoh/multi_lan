import json
import yaml
from yaml import Loader

def yaml_to_json(yaml_file_path: str) -> str:
    '''Webszolgáltatás backend, amely egy YAML fájlt JSON karakterlánccá alakít. A függvény beolvassa a YAML fájl tartalmát a megadott elérési útról, JSON formátumra alakítja, és visszaadja a JSON karakterláncot. Ha hiba lép fel, például fájl nem található, érvénytelen YAML tartalom vagy a tartalom nem alakítható JSON-ra, akkor az 'Hiba: ' kezdetű hibaüzenetet adja vissza.

    Args:
        yaml_file_path: A YAML fájl elérési útja, amelyet konvertálni kell.

    Returns:
        str: A YAML fájlból konvertált JSON karakterlánc, vagy egy 'Hiba: ' kezdetű hibaüzenet.'''
    try:
        with open(yaml_file_path, 'r') as yaml_file:
            yaml_content = yaml.load(yaml_file, Loader=Loader)
            json_content = json.dumps(yaml_content)
            return json_content
    except FileNotFoundError:
        return 'Hiba: Fájl nem található'
    except yaml.YAMLError:
        return 'Hiba: Érvénytelen YAML tartalom'
    except json.JSONDecodeError:
        return 'Hiba: A tartalom nem alakítható JSON-ra'