import json
import yaml
from yaml import Loader


def yaml_to_json(yaml_file_path: str) -> str:
    '''YAML 파일을 JSON 문자열로 변환하는 웹 서비스의 백엔드입니다. 이 함수는 주어진 경로에서 YAML 파일의 내용을 읽고, 이를 JSON 형식으로 변환하여 JSON 문자열을 반환합니다. 파일을 찾을 수 없거나, 잘못된 YAML 내용이거나, 내용을 JSON으로 변환할 수 없는 경우와 같은 오류가 발생하면 'Error: '로 시작하는 오류 메시지를 반환합니다.

    Args:
        yaml_file_path: 변환할 YAML 파일의 경로입니다.

    Returns:
        str: YAML 파일에서 변환된 JSON 문자열 또는 'Error: '로 시작하는 오류 메시지입니다.'''
    try:
        with open(yaml_file_path, 'r', encoding='utf-8') as file:
            yaml_content = file.read()
        
        data = yaml.load(yaml_content, Loader=Loader)
        json_string = json.dumps(data, ensure_ascii=False, indent=2)
        return json_string
    
    except FileNotFoundError:
        return f"Error: File not found at path '{yaml_file_path}'"
    except yaml.YAMLError as e:
        return f"Error: Invalid YAML content - {str(e)}"
    except (TypeError, ValueError) as e:
        return f"Error: Cannot convert content to JSON - {str(e)}"
    except Exception as e:
        return f"Error: Unexpected error - {str(e)}"