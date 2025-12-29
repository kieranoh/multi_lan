import json
import yaml
from yaml import Loader
import os


def yaml_to_json(yaml_file_path: str) -> str:
    '''Backend dla usługi internetowej, która konwertuje plik YAML na ciąg JSON. Funkcja odczytuje zawartość pliku YAML z podanej ścieżki, konwertuje ją na format JSON i zwraca ciąg JSON. W przypadku wystąpienia błędu, takiego jak brak pliku, nieprawidłowa zawartość YAML lub zawartość, która nie może być skonwertowana na JSON, zwróć komunikat o błędzie zaczynający się od 'Error: '.

    Args:
        yaml_file_path: Ścieżka do pliku YAML do konwersji.

    Returns:
        str: Ciąg JSON skonwertowany z pliku YAML lub komunikat o błędzie zaczynający się od 'Error: '.'''
    try:
        # Sprawdzenie czy plik istnieje
        if not os.path.exists(yaml_file_path):
            return f"Error: File '{yaml_file_path}' not found."
        
        # Otwarcie i odczytanie pliku YAML
        with open(yaml_file_path, 'r', encoding='utf-8') as file:
            yaml_content = file.read()
        
        # Sprawdzenie czy plik nie jest pusty
        if not yaml_content.strip():
            return "Error: YAML file is empty."
        
        # Parsowanie zawartości YAML
        parsed_yaml = yaml.load(yaml_content, Loader=Loader)
        
        # Konwersja do JSON z zachowaniem polskich znaków i ładnym formatowaniem
        json_string = json.dumps(parsed_yaml, ensure_ascii=False, indent=2)
        
        return json_string
        
    except yaml.YAMLError as e:
        return f"Error: Invalid YAML content - {str(e)}"
    except json.JSONEncodeError as e:
        return f"Error: Cannot convert to JSON - {str(e)}"
    except PermissionError:
        return f"Error: Permission denied when accessing '{yaml_file_path}'."
    except IsADirectoryError:
        return f"Error: '{yaml_file_path}' is a directory, not a file."
    except UnicodeDecodeError:
        return f"Error: Cannot decode file '{yaml_file_path}' with UTF-8 encoding."
    except Exception as e:
        return f"Error: Unexpected error - {str(e)}"