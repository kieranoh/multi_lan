import json
import yaml
from yaml import Loader

def yaml_to_json(yaml_file_path: str) -> str:
    '''Backend para un servicio web que convierte un archivo YAML a una cadena JSON. La función lee el contenido del archivo YAML desde la ruta dada, lo convierte a formato JSON y devuelve la cadena JSON. Si hay algún error, como archivo no encontrado, contenido YAML inválido o el contenido no se puede convertir a JSON, devuelve el mensaje de error que comienza con 'Error: '.

    Args:
        yaml_file_path: La ruta al archivo YAML a convertir.

    Returns:
        str: La cadena JSON convertida del archivo YAML, o un mensaje de error que comienza con 'Error: '.'''
    try:
        with open(yaml_file_path, 'r') as yaml_file:
            yaml_content = yaml.load(yaml_file, Loader=Loader)
            json_content = json.dumps(yaml_content)
            return json_content
    except FileNotFoundError:
        return 'Error: El archivo no se encuentra.'
    except yaml.YAMLError as e:
        return f'Error: Contenido YAML inválido. {str(e)}'
    except json.JSONDecodeError as e:
        return f'Error: No se pudo convertir a JSON. {str(e)}'
    except Exception as e:
        return f'Error: {str(e)}'