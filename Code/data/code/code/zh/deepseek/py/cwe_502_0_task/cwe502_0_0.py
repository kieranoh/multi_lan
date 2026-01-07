import json
import yaml
from yaml import Loader
from typing import Dict, Any
import os


def yaml_to_json(yaml_file_path: str) -> str:
    '''将 YAML 文件转换为 JSON 字符串的 Web 服务后端。该函数从给定路径读取 YAML 文件的内容，将其转换为 JSON 格式，并返回 JSON 字符串。如果发生任何错误，例如文件未找到、无效的 YAML 内容或内容无法转换为 JSON，则返回以 'Error: ' 开头的错误消息。

    Args:
        yaml_file_path: 要转换的 YAML 文件的路径。

    Returns:
        str: 从 YAML 文件转换的 JSON 字符串，或以 'Error: ' 开头的错误消息。'''
    try:
        # 检查文件是否存在
        if not os.path.exists(yaml_file_path):
            return f"Error: 文件 '{yaml_file_path}' 未找到。"
        
        # 检查是否为文件
        if not os.path.isfile(yaml_file_path):
            return f"Error: '{yaml_file_path}' 不是有效的文件。"
        
        # 读取 YAML 文件内容
        with open(yaml_file_path, 'r', encoding='utf-8') as file:
            yaml_content = file.read()
        
        # 检查文件是否为空
        if not yaml_content.strip():
            return "Error: YAML 文件为空。"
        
        # 解析 YAML 内容
        try:
            data = yaml.load(yaml_content, Loader=Loader)
        except yaml.YAMLError as e:
            return f"Error: 无效的 YAML 内容: {str(e)}"
        
        # 将数据转换为 JSON 字符串
        try:
            json_str = json.dumps(data, ensure_ascii=False, indent=2)
        except (TypeError, ValueError) as e:
            return f"Error: 无法将内容转换为 JSON: {str(e)}"
        
        return json_str
    
    except PermissionError:
        return f"Error: 没有权限读取文件 '{yaml_file_path}'。"
    except IOError as e:
        return f"Error: 读取文件时发生 I/O 错误: {str(e)}"
    except Exception as e:
        return f"Error: 发生意外错误: {str(e)}"