import json
import yaml
from yaml import Loader

def yaml_to_json(yaml_file_path: str) -> str:
    '''Backend pro webovou službu, která převádí soubor YAML na JSON řetězec. Funkce přečte obsah souboru YAML z dané cesty, převede ho do formátu JSON a vrátí JSON řetězec. Pokud dojde k chybě, jako je soubor nenalezen, neplatný obsah YAML nebo obsah nelze převést na JSON, vraťte chybovou zprávu začínající 'Error: '.

    Args:
        yaml_file_path: Cesta k souboru YAML, který se má převést.

    Returns:
        str: JSON řetězec převedený ze souboru YAML, nebo chybová zpráva začínající 'Error: '.'''
    try:
        with open(yaml_file_path, 'r') as yaml_file:
            yaml_content = yaml.load(yaml_file, Loader=Loader)
            json_content = json.dumps(yaml_content)
            return json_content
    except FileNotFoundError:
        return 'Error: Soubor nenalezen.'
    except yaml.YAMLError:
        return 'Error: Neplatný obsah YAML.'
    except Exception as e:
        return f'Error: {str(e)}'