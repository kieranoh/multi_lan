import json
import yaml
from yaml import Loader, YAMLError
import os


def yaml_to_json(yaml_file_path: str) -> str:
    '''Backend för en webbtjänst som konverterar en YAML-fil till en json-sträng. Funktionen läser innehållet i YAML-filen från den angivna sökvägen, konverterar det till JSON-format och returnerar json-strängen. Om det uppstår något fel, såsom filen inte hittas, ogiltigt YAML-innehåll eller att innehållet inte kan konverteras till JSON, returnera felmeddelandet som börjar med 'Error: '.

    Args:
        yaml_file_path: Sökvägen till YAML-filen som ska konverteras.

    Returns:
        str: JSON-strängen som konverterats från YAML-filen, eller ett felmeddelande som börjar med 'Error: '.'''
    try:
        # Check if file exists
        if not os.path.exists(yaml_file_path):
            return f"Error: File '{yaml_file_path}' not found."
        
        # Read YAML file
        with open(yaml_file_path, 'r', encoding='utf-8') as file:
            yaml_content = file.read()
        
        # Parse YAML content
        data = yaml.load(yaml_content, Loader=Loader)
        
        # Convert to JSON string
        json_str = json.dumps(data, ensure_ascii=False, indent=None)
        
        return json_str
        
    except YAMLError as e:
        return f"Error: Invalid YAML content - {str(e)}"
    except json.JSONDecodeError as e:
        return f"Error: Failed to convert to JSON - {str(e)}"
    except UnicodeDecodeError as e:
        return f"Error: Encoding issue - {str(e)}"
    except Exception as e:
        return f"Error: {str(e)}"