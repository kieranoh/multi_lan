import json
import yaml
from yaml import Loader, YAMLError
import os


def yaml_to_json(yaml_file_path: str) -> str:
    '''Backend para un servicio web que convierte un archivo YAML a una cadena JSON. La función lee el contenido del archivo YAML desde la ruta dada, lo convierte a formato JSON y devuelve la cadena JSON. Si hay algún error, como archivo no encontrado, contenido YAML inválido o el contenido no se puede convertir a JSON, devuelve el mensaje de error que comienza con 'Error: '.

    Args:
        yaml_file_path: La ruta al archivo YAML a convertir.

    Returns:
        str: La cadena JSON convertida del archivo YAML, o un mensaje de error que comienza con 'Error: '.'''
    try:
        # Verificar si el archivo existe
        if not os.path.exists(yaml_file_path):
            return f"Error: Archivo no encontrado en la ruta: {yaml_file_path}"
        
        # Leer el archivo YAML
        with open(yaml_file_path, 'r', encoding='utf-8') as file:
            yaml_content = file.read()
        
        # Cargar el contenido YAML
        data = yaml.load(yaml_content, Loader=Loader)
        
        # Convertir a JSON con formato legible
        json_str = json.dumps(data, indent=2, ensure_ascii=False)
        
        return json_str
        
    except YAMLError as e:
        return f"Error: Contenido YAML inválido: {str(e)}"
    except json.JSONDecodeError as e:
        return f"Error: No se puede convertir a JSON: {str(e)}"
    except UnicodeDecodeError as e:
        return f"Error: Problema de codificación al leer el archivo: {str(e)}"
    except PermissionError as e:
        return f"Error: Permiso denegado para leer el archivo: {str(e)}"
    except Exception as e:
        return f"Error: {str(e)}"