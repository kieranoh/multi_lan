import json
import yaml
from yaml import Loader

def yaml_to_json(yaml_file_path: str) -> str:
    '''Бэкенд для веб-сервиса, который конвертирует файл YAML в строку JSON. Функция считывает содержимое файла YAML по указанному пути, конвертирует его в формат JSON и возвращает строку JSON. Если возникает ошибка, такая как файл не найден, недопустимое содержимое YAML или содержимое не может быть конвертировано в JSON, возвращается сообщение об ошибке, начинающееся с 'Ошибка: '.

    Args:
        yaml_file_path: Путь к файлу YAML для конвертации.

    Returns:
        str: Строка JSON, конвертированная из файла YAML, или сообщение об ошибке, начинающееся с 'Ошибка: '.'''
    try:
        with open(yaml_file_path, 'r') as yaml_file:
            yaml_content = yaml.load(yaml_file, Loader=Loader)
            json_content = json.dumps(yaml_content)
            return json_content
    except FileNotFoundError:
        return 'Ошибка: Файл не найден.'
    except yaml.YAMLError:
        return 'Ошибка: Недопустимое содержимое YAML.'
    except Exception as e:
        return f'Ошибка: {str(e)}'