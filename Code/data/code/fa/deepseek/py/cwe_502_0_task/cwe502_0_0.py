import json
import yaml
from yaml import Loader
import os


def yaml_to_json(yaml_file_path: str) -> str:
    '''Backend برای یک سرویس وب که یک فایل YAML را به رشته JSON تبدیل می‌کند. این تابع محتوای فایل YAML را از مسیر داده شده می‌خواند، آن را به فرمت JSON تبدیل می‌کند و رشته JSON را برمی‌گرداند. اگر خطایی وجود داشته باشد، مانند عدم وجود فایل، محتوای YAML نامعتبر یا عدم امکان تبدیل محتوا به JSON، پیام خطا را با 'Error: ' شروع کنید.

    Args:
        yaml_file_path: مسیر فایل YAML برای تبدیل.

    Returns:
        str: رشته JSON تبدیل شده از فایل YAML، یا یک پیام خطا که با 'Error: ' شروع می‌شود.'''
    try:
        # بررسی وجود فایل
        if not os.path.exists(yaml_file_path):
            return f"Error: File not found at path: {yaml_file_path}"
        
        # خواندن فایل YAML
        with open(yaml_file_path, 'r', encoding='utf-8') as file:
            yaml_content = file.read()
        
        # بارگذاری محتوای YAML
        data = yaml.load(yaml_content, Loader=Loader)
        
        # تبدیل به JSON با فرمت‌دهی مناسب
        json_str = json.dumps(data, ensure_ascii=False, indent=2)
        
        return json_str
    
    except yaml.YAMLError as e:
        return f"Error: Invalid YAML content: {str(e)}"
    except json.JSONDecodeError as e:
        return f"Error: Failed to convert to JSON: {str(e)}"
    except UnicodeDecodeError as e:
        return f"Error: Encoding issue while reading file: {str(e)}"
    except PermissionError as e:
        return f"Error: Permission denied: {str(e)}"
    except Exception as e:
        return f"Error: Unexpected error: {str(e)}"