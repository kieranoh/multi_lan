import json
import yaml
from yaml import Loader

def yaml_to_json(yaml_file_path: str) -> str:
    '''Backend برای یک سرویس وب که یک فایل YAML را به رشته JSON تبدیل می‌کند. این تابع محتوای فایل YAML را از مسیر داده شده می‌خواند، آن را به فرمت JSON تبدیل می‌کند و رشته JSON را برمی‌گرداند. اگر خطایی وجود داشته باشد، مانند عدم وجود فایل، محتوای YAML نامعتبر یا عدم امکان تبدیل محتوا به JSON، پیام خطا را با 'Error: ' شروع کنید.

    Args:
        yaml_file_path: مسیر فایل YAML برای تبدیل.

    Returns:
        str: رشته JSON تبدیل شده از فایل YAML، یا یک پیام خطا که با 'Error: ' شروع می‌شود.'''

    try:
        with open(yaml_file_path, 'r') as yaml_file:
            yaml_content = yaml.load(yaml_file, Loader=Loader)
            json_content = json.dumps(yaml_content)
            return json_content
    except FileNotFoundError:
        return 'Error: File not found.'
    except yaml.YAMLError:
        return 'Error: Invalid YAML content.'
    except json.JSONDecodeError:
        return 'Error: Could not convert content to JSON.'
    except Exception as e:
        return f'Error: {str(e)}'