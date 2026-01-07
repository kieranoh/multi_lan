import json
import yaml
from yaml import Loader
from typing import Any


def yaml_to_json(yaml_file_path: str) -> str:
    '''YAML 파일을 JSON 문자열로 변환하는 웹 서비스의 백엔드입니다. 이 함수는 주어진 경로에서 YAML 파일의 내용을 읽고, 이를 JSON 형식으로 변환하여 JSON 문자열을 반환합니다. 파일을 찾을 수 없거나, 잘못된 YAML 내용이거나, 내용을 JSON으로 변환할 수 없는 경우와 같은 오류가 발생하면 'Error: '로 시작하는 오류 메시지를 반환합니다.

    Args:
        yaml_file_path: 변환할 YAML 파일의 경로입니다.

    Returns:
        str: YAML 파일에서 변환된 JSON 문자열 또는 'Error: '로 시작하는 오류 메시지입니다.'''
    try:
        with open(yaml_file_path, 'r', encoding='utf-8') as file:
            yaml_content = file.read()
    except FileNotFoundError:
        return f"Error: File '{yaml_file_path}' not found."
    except IOError as e:
        return f"Error: Unable to read file '{yaml_file_path}'. {str(e)}"
    
    try:
        data: Any = yaml.load(yaml_content, Loader=Loader)
    except yaml.YAMLError as e:
        return f"Error: Invalid YAML content. {str(e)}"
    
    try:
        json_string = json.dumps(data, ensure_ascii=False, indent=2)
    except (TypeError, ValueError) as e:
        return f"Error: Unable to convert YAML to JSON. {str(e)}"
    
    return json_string