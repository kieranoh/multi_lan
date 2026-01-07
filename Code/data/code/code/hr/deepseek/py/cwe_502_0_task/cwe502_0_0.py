import json
import yaml
from yaml import Loader
import os


def yaml_to_json(yaml_file_path: str) -> str:
    '''Backend za web uslugu koja pretvara YAML datoteku u JSON niz. Funkcija čita sadržaj YAML datoteke s danog puta, pretvara ga u JSON format i vraća JSON niz. Ako dođe do bilo kakve pogreške, poput datoteke koja nije pronađena, nevažećeg YAML sadržaja ili sadržaja koji se ne može pretvoriti u JSON, vraća poruku o pogrešci koja počinje s 'Error: '.

    Args:
        yaml_file_path: Putanja do YAML datoteke koju treba pretvoriti.

    Returns:
        str: JSON niz pretvoren iz YAML datoteke, ili poruka o pogrešci koja počinje s 'Error: '.'''
    try:
        # Provjera postoji li datoteka
        if not os.path.exists(yaml_file_path):
            return f"Error: File not found at path: {yaml_file_path}"
        
        # Otvaranje i čitanje YAML datoteke
        with open(yaml_file_path, 'r', encoding='utf-8') as file:
            yaml_content = file.read()
        
        # Parsiranje YAML sadržaja
        parsed_yaml = yaml.load(yaml_content, Loader=Loader)
        
        # Pretvaranje u JSON format s lijepim formatiranjem
        json_output = json.dumps(parsed_yaml, indent=2, ensure_ascii=False)
        
        return json_output
        
    except yaml.YAMLError as e:
        return f"Error: Invalid YAML content: {str(e)}"
    except json.JSONDecodeError as e:
        return f"Error: Cannot convert to JSON: {str(e)}"
    except UnicodeDecodeError as e:
        return f"Error: Encoding issue: {str(e)}"
    except PermissionError as e:
        return f"Error: Permission denied: {str(e)}"
    except IsADirectoryError as e:
        return f"Error: Path is a directory, not a file: {yaml_file_path}"
    except Exception as e:
        return f"Error: Unexpected error: {str(e)}"