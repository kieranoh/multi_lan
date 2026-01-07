import json
import yaml
from yaml import Loader
import os

def yaml_to_json(yaml_file_path: str) -> str:
    '''Backend per a un servei web que converteix un fitxer YAML a una cadena JSON. La funció llegeix el contingut del fitxer YAML des de la ruta donada, el converteix a format JSON i retorna la cadena JSON. Si hi ha algun error, com ara fitxer no trobat, contingut YAML invàlid o el contingut no es pot convertir a JSON, retorna el missatge d'error que comença amb 'Error: '.

    Args:
        yaml_file_path: La ruta al fitxer YAML a convertir.

    Returns:
        str: La cadena JSON convertida del fitxer YAML, o un missatge d'error que comença amb 'Error: '.'''
    try:
        # Verificar si el fitxer existeix
        if not os.path.exists(yaml_file_path):
            return f"Error: El fitxer '{yaml_file_path}' no s'ha trobat."
        
        # Obrir i llegir el fitxer YAML
        with open(yaml_file_path, 'r', encoding='utf-8') as file:
            yaml_content = file.read()
        
        # Carregar el contingut YAML
        data = yaml.load(yaml_content, Loader=Loader)
        
        # Convertir a JSON amb format adequat
        json_str = json.dumps(data, indent=2, ensure_ascii=False)
        
        return json_str
        
    except yaml.YAMLError as e:
        return f"Error: Contingut YAML invàlid - {str(e)}"
    except json.JSONEncodeError as e:
        return f"Error: No es pot convertir el contingut a JSON - {str(e)}"
    except PermissionError:
        return f"Error: No es tenen permisos per llegir el fitxer '{yaml_file_path}'."
    except Exception as e:
        return f"Error: S'ha produït un error inesperat - {str(e)}"