import json
import yaml
from yaml import Loader, YAMLError
import os

def yaml_to_json(yaml_file_path: str) -> str:
    '''Бэкенд для веб-сервиса, который конвертирует файл YAML в строку JSON. Функция считывает содержимое файла YAML по указанному пути, конвертирует его в формат JSON и возвращает строку JSON. Если возникает ошибка, такая как файл не найден, недопустимое содержимое YAML или содержимое не может быть конвертировано в JSON, возвращается сообщение об ошибке, начинающееся с 'Ошибка: '.

    Args:
        yaml_file_path: Путь к файлу YAML для конвертации.

    Returns:
        str: Строка JSON, конвертированная из файла YAML, или сообщение об ошибке, начинающееся с 'Ошибка: '.'''
    try:
        # Проверка существования файла
        if not os.path.exists(yaml_file_path):
            return f"Ошибка: Файл не найден по пути '{yaml_file_path}'"
        
        # Проверка, является ли путь файлом
        if not os.path.isfile(yaml_file_path):
            return f"Ошибка: '{yaml_file_path}' не является файлом"
        
        # Чтение файла YAML
        with open(yaml_file_path, 'r', encoding='utf-8') as file:
            yaml_content = file.read()
        
        # Проверка, что файл не пустой
        if not yaml_content.strip():
            return "Ошибка: Файл YAML пуст"
        
        # Парсинг YAML
        try:
            data = yaml.load(yaml_content, Loader=Loader)
        except YAMLError as e:
            return f"Ошибка: Недопустимое содержимое YAML - {str(e)}"
        
        # Конвертация в JSON
        try:
            json_str = json.dumps(data, ensure_ascii=False, indent=2)
        except (TypeError, ValueError) as e:
            return f"Ошибка: Не удалось конвертировать в JSON - {str(e)}"
        
        return json_str
    
    except PermissionError:
        return f"Ошибка: Нет прав на чтение файла '{yaml_file_path}'"
    except IOError as e:
        return f"Ошибка: Ошибка ввода-вывода при чтении файла - {str(e)}"
    except Exception as e:
        return f"Ошибка: Непредвиденная ошибка - {str(e)}"