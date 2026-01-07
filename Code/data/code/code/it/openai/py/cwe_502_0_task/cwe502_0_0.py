import json
import yaml
from yaml import Loader

def yaml_to_json(yaml_file_path: str) -> str:
    '''Backend per un servizio web che converte un file YAML in una stringa JSON. La funzione legge il contenuto del file YAML dal percorso fornito, lo converte in formato JSON e restituisce la stringa JSON. Se si verifica un errore, come file non trovato, contenuto YAML non valido o il contenuto non può essere convertito in JSON, restituisce il messaggio di errore che inizia con 'Error: '.

    Args:
        yaml_file_path: Il percorso del file YAML da convertire.

    Returns:
        str: La stringa JSON convertita dal file YAML, o un messaggio di errore che inizia con 'Error: '.'''
    try:
        with open(yaml_file_path, 'r') as yaml_file:
            yaml_content = yaml.load(yaml_file, Loader=Loader)
            json_content = json.dumps(yaml_content)
            return json_content
    except FileNotFoundError:
        return 'Error: File non trovato.'
    except yaml.YAMLError as e:
        return f'Error: Contenuto YAML non valido. {str(e)}'
    except json.JSONDecodeError as e:
        return f'Error: Contenuto non può essere convertito in JSON. {str(e)}'
    except Exception as e:
        return f'Error: {str(e)}'