import json
import yaml
from yaml import Loader
from typing import Any
import os


def yaml_to_json(yaml_file_path: str) -> str:
    '''Webszolgáltatás backend, amely egy YAML fájlt JSON karakterlánccá alakít. A függvény beolvassa a YAML fájl tartalmát a megadott elérési útról, JSON formátumra alakítja, és visszaadja a JSON karakterláncot. Ha hiba lép fel, például fájl nem található, érvénytelen YAML tartalom vagy a tartalom nem alakítható JSON-ra, akkor az 'Hiba: ' kezdetű hibaüzenetet adja vissza.

    Args:
        yaml_file_path: A YAML fájl elérési útja, amelyet konvertálni kell.

    Returns:
        str: A YAML fájlból konvertált JSON karakterlánc, vagy egy 'Hiba: ' kezdetű hibaüzenet.'''
    try:
        # Ellenőrizzük, hogy a fájl létezik-e
        if not os.path.exists(yaml_file_path):
            return f"Hiba: A fájl nem található: {yaml_file_path}"
        
        # Beolvassuk a YAML fájl tartalmát
        with open(yaml_file_path, 'r', encoding='utf-8') as file:
            yaml_content = file.read()
        
        # Parse-oljuk a YAML tartalmat
        parsed_yaml = yaml.load(yaml_content, Loader=Loader)
        
        # Konvertáljuk JSON formátumra
        # ensure_ascii=False biztosítja, hogy Unicode karakterek megfelelően jelenjenek meg
        # indent=4 formázott kimenetet biztosít
        json_output = json.dumps(parsed_yaml, ensure_ascii=False, indent=4)
        
        return json_output
        
    except yaml.YAMLError as e:
        return f"Hiba: Érvénytelen YAML tartalom: {str(e)}"
    except json.JSONDecodeError as e:
        return f"Hiba: A tartalom nem alakítható JSON-ra: {str(e)}"
    except UnicodeDecodeError as e:
        return f"Hiba: Karakterkódolási hiba: {str(e)}"
    except PermissionError as e:
        return f"Hiba: Nincs jogosultság a fájl olvasásához: {str(e)}"
    except Exception as e:
        return f"Hiba: Váratlan hiba történt: {str(e)}"