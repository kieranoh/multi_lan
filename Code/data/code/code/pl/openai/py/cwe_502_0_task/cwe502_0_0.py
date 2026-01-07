import json
import yaml
from yaml import Loader

def yaml_to_json(yaml_file_path: str) -> str:
    '''Backend dla usługi internetowej, która konwertuje plik YAML na ciąg JSON. Funkcja odczytuje zawartość pliku YAML z podanej ścieżki, konwertuje ją na format JSON i zwraca ciąg JSON. W przypadku wystąpienia błędu, takiego jak brak pliku, nieprawidłowa zawartość YAML lub zawartość, która nie może być skonwertowana na JSON, zwróć komunikat o błędzie zaczynający się od 'Error: '.

    Args:
        yaml_file_path: Ścieżka do pliku YAML do konwersji.

    Returns:
        str: Ciąg JSON skonwertowany z pliku YAML lub komunikat o błędzie zaczynający się od 'Error: '.'''
    try:
        with open(yaml_file_path, 'r') as yaml_file:
            yaml_content = yaml.load(yaml_file, Loader=Loader)
            json_content = json.dumps(yaml_content)
            return json_content
    except FileNotFoundError:
        return 'Error: File not found.'
    except yaml.YAMLError as e:
        return f'Error: Invalid YAML content. {str(e)}'
    except json.JSONDecodeError as e:
        return f'Error: Content cannot be converted to JSON. {str(e)}'
    except Exception as e:
        return f'Error: {str(e)}'