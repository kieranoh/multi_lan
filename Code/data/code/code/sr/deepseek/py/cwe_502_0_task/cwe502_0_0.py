import json
import yaml
from yaml import Loader
from typing import Any


def yaml_to_json(yaml_file_path: str) -> str:
    '''Backend za veb servis koji konvertuje YAML datoteku u JSON string. Funkcija čita sadržaj YAML datoteke sa date putanje, konvertuje ga u JSON format i vraća JSON string. Ako dođe do greške, kao što su datoteka nije pronađena, nevalidan YAML sadržaj ili sadržaj ne može biti konvertovan u JSON, vraća poruku o grešci koja počinje sa 'Error: '.

    Args:
        yaml_file_path: Putanja do YAML datoteke koja treba da se konvertuje.

    Returns:
        str: JSON string konvertovan iz YAML datoteke, ili poruku o grešci koja počinje sa 'Error: '.'''
    try:
        # Otvaranje i čitanje YAML datoteke
        with open(yaml_file_path, 'r', encoding='utf-8') as file:
            yaml_content = file.read()
        
        # Parsiranje YAML sadržaja
        parsed_yaml = yaml.load(yaml_content, Loader=Loader)
        
        # Konverzija u JSON string sa lepim formatiranjem
        json_string = json.dumps(parsed_yaml, indent=2, ensure_ascii=False)
        
        return json_string
    
    except FileNotFoundError:
        return f"Error: Datoteka '{yaml_file_path}' nije pronađena."
    
    except yaml.YAMLError as e:
        return f"Error: Nevalidan YAML sadržaj: {str(e)}"
    
    except (TypeError, ValueError) as e:
        return f"Error: Sadržaj ne može biti konvertovan u JSON: {str(e)}"
    
    except Exception as e:
        return f"Error: Neočekivana greška: {str(e)}"