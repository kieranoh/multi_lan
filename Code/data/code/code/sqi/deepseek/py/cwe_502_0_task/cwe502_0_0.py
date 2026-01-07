import json
import yaml
from yaml import Loader, YAMLError
import os


def yaml_to_json(yaml_file_path: str) -> str:
    '''YAML 파일을 JSON 문자열로 변환하는 웹 서비스의 백엔드입니다. 이 함수는 주어진 경로에서 YAML 파일의 내용을 읽고, 이를 JSON 형식으로 변환하여 JSON 문자열을 반환합니다. 파일을 찾을 수 없거나, 잘못된 YAML 내용이거나, 내용을 JSON으로 변환할 수 없는 경우 'Error: '로 시작하는 오류 메시지를 반환합니다.

    Args:
        yaml_file_path: 변환할 YAML 파일의 경로입니다.

    Returns:
        str: YAML 파일에서 변환된 JSON 문자열 또는 'Error: '로 시작하는 오류 메시지.'''
    try:
        # 파일 존재 여부 확인
        if not os.path.exists(yaml_file_path):
            return f"Error: File not found at path '{yaml_file_path}'"
        
        # YAML 파일 읽기
        with open(yaml_file_path, 'r', encoding='utf-8') as file:
            yaml_content = file.read()
        
        # YAML 파싱
        data = yaml.load(yaml_content, Loader=Loader)
        
        # JSON으로 변환
        json_str = json.dumps(data, ensure_ascii=False, indent=2)
        return json_str
        
    except YAMLError as e:
        return f"Error: Invalid YAML content - {str(e)}"
    except json.JSONDecodeError as e:
        return f"Error: Failed to convert to JSON - {str(e)}"
    except UnicodeDecodeError as e:
        return f"Error: Encoding issue - {str(e)}"
    except PermissionError as e:
        return f"Error: Permission denied - {str(e)}"
    except IsADirectoryError as e:
        return f"Error: Path is a directory, not a file - {str(e)}"
    except Exception as e:
        return f"Error: Unexpected error - {str(e)}"