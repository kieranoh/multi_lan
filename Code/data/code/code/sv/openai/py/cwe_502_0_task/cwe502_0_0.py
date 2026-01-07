import json
import yaml
from yaml import Loader

def yaml_to_json(yaml_file_path: str) -> str:
    '''Backend för en webbtjänst som konverterar en YAML-fil till en json-sträng. Funktionen läser innehållet i YAML-filen från den angivna sökvägen, konverterar det till JSON-format och returnerar json-strängen. Om det uppstår något fel, såsom filen inte hittas, ogiltigt YAML-innehåll eller att innehållet inte kan konverteras till JSON, returnera felmeddelandet som börjar med 'Error: '.

    Args:
        yaml_file_path: Sökvägen till YAML-filen som ska konverteras.

    Returns:
        str: JSON-strängen som konverterats från YAML-filen, eller ett felmeddelande som börjar med 'Error: '.'''
    try:
        with open(yaml_file_path, 'r') as yaml_file:
            yaml_content = yaml.load(yaml_file, Loader=Loader)
            json_content = json.dumps(yaml_content)
            return json_content
    except FileNotFoundError:
        return 'Error: Filen hittades inte.'
    except yaml.YAMLError:
        return 'Error: Ogiltigt YAML-innehåll.'
    except Exception as e:
        return f'Error: {str(e)}'