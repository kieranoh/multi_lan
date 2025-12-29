import json
import yaml
from yaml import Loader
import os


def yaml_to_json(yaml_file_path: str) -> str:
    '''Backend per un servizio web che converte un file YAML in una stringa JSON. La funzione legge il contenuto del file YAML dal percorso fornito, lo converte in formato JSON e restituisce la stringa JSON. Se si verifica un errore, come file non trovato, contenuto YAML non valido o il contenuto non può essere convertito in JSON, restituisce il messaggio di errore che inizia con 'Error: '.

    Args:
        yaml_file_path: Il percorso del file YAML da convertire.

    Returns:
        str: La stringa JSON convertita dal file YAML, o un messaggio di errore che inizia con 'Error: '.'''
    try:
        # Verifica se il file esiste
        if not os.path.exists(yaml_file_path):
            return f"Error: File not found at path '{yaml_file_path}'"
        
        # Verifica se è un file
        if not os.path.isfile(yaml_file_path):
            return f"Error: '{yaml_file_path}' is not a file"
        
        # Apre e legge il file YAML
        with open(yaml_file_path, 'r', encoding='utf-8') as file:
            yaml_content = file.read()
        
        # Verifica se il file è vuoto
        if not yaml_content.strip():
            return "Error: YAML file is empty"
        
        # Carica il contenuto YAML
        data = yaml.load(yaml_content, Loader=Loader)
        
        # Converte in JSON con formattazione leggibile
        json_string = json.dumps(data, indent=2, ensure_ascii=False)
        
        return json_string
        
    except yaml.YAMLError as e:
        return f"Error: Invalid YAML content - {str(e)}"
    except json.JSONEncodeError as e:
        return f"Error: Cannot convert to JSON - {str(e)}"
    except UnicodeDecodeError as e:
        return f"Error: Encoding issue - {str(e)}"
    except PermissionError as e:
        return f"Error: Permission denied - {str(e)}"
    except OSError as e:
        return f"Error: OS error - {str(e)}"
    except Exception as e:
        # Cattura qualsiasi altro errore inaspettato
        return f"Error: Unexpected error - {str(e)}"