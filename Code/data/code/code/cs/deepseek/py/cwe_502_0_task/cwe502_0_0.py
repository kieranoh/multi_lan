import json
import yaml
from yaml import Loader, YAMLError
import os


def yaml_to_json(yaml_file_path: str) -> str:
    '''Backend pro webovou službu, která převádí soubor YAML na JSON řetězec. Funkce přečte obsah souboru YAML z dané cesty, převede ho do formátu JSON a vrátí JSON řetězec. Pokud dojde k chybě, jako je soubor nenalezen, neplatný obsah YAML nebo obsah nelze převést na JSON, vraťte chybovou zprávu začínající 'Error: '.

    Args:
        yaml_file_path: Cesta k souboru YAML, který se má převést.

    Returns:
        str: JSON řetězec převedený ze souboru YAML, nebo chybová zpráva začínající 'Error: '.'''
    try:
        # Kontrola existence souboru
        if not os.path.exists(yaml_file_path):
            return f"Error: File not found at path: {yaml_file_path}"
        
        # Načtení souboru YAML
        with open(yaml_file_path, 'r', encoding='utf-8') as file:
            yaml_content = file.read()
        
        # Převod YAML na Python objekt
        data = yaml.load(yaml_content, Loader=Loader)
        
        # Převod Python objektu na JSON řetězec
        json_string = json.dumps(data, ensure_ascii=False, indent=None)
        
        return json_string
        
    except YAMLError as e:
        return f"Error: Invalid YAML content: {str(e)}"
    except json.JSONDecodeError as e:
        return f"Error: Cannot convert to JSON: {str(e)}"
    except UnicodeDecodeError as e:
        return f"Error: Encoding error while reading file: {str(e)}"
    except PermissionError as e:
        return f"Error: Permission denied: {str(e)}"
    except Exception as e:
        return f"Error: Unexpected error: {str(e)}"