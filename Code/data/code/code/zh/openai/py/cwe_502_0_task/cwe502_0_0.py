import json
import yaml
from yaml import Loader

def yaml_to_json(yaml_file_path: str) -> str:
    '''将 YAML 文件转换为 JSON 字符串的 Web 服务后端。该函数从给定路径读取 YAML 文件的内容，将其转换为 JSON 格式，并返回 JSON 字符串。如果发生任何错误，例如文件未找到、无效的 YAML 内容或内容无法转换为 JSON，则返回以 'Error: ' 开头的错误消息。

    Args:
        yaml_file_path: 要转换的 YAML 文件的路径。

    Returns:
        str: 从 YAML 文件转换的 JSON 字符串，或以 'Error: ' 开头的错误消息。'''
    
    try:
        with open(yaml_file_path, 'r', encoding='utf-8') as yaml_file:
            yaml_content = yaml.load(yaml_file, Loader=Loader)
            json_content = json.dumps(yaml_content, ensure_ascii=False)
            return json_content
    except FileNotFoundError:
        return f'Error: 文件未找到 {yaml_file_path}'
    except yaml.YAMLError as e:
        return f'Error: 无效的 YAML 内容 - {str(e)}'
    except Exception as e:
        return f'Error: {str(e)}'