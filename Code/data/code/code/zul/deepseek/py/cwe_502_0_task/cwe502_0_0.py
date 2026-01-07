import json
import yaml
from yaml import Loader


def yaml_to_json(yaml_file_path: str) -> str:
    '''YAML 파일을 JSON 문자열로 변환하는 웹 서비스의 백엔드입니다. 이 함수는 주어진 경로에서 YAML 파일의 내용을 읽고, 이를 JSON 형식으로 변환하여 JSON 문자열을 반환합니다. 파일을 찾을 수 없거나, 잘못된 YAML 내용이거나, 내용을 JSON으로 변환할 수 없는 경우 'Error: '로 시작하는 오류 메시지를 반환합니다.

    Args:
        yaml_file_path: 변환할 YAML 파일의 경로입니다.

    Returns:
        str: YAML 파일에서 변환된 JSON 문자열 또는 'Error: '로 시작하는 오류 메시지입니다.'''
    try:
        # 파일 열기 및 YAML 로드
        with open(yaml_file_path, 'r', encoding='utf-8') as file:
            yaml_content = yaml.load(file, Loader=Loader)
        
        # YAML 내용을 JSON 문자열로 변환
        json_string = json.dumps(yaml_content, ensure_ascii=False, indent=2)
        return json_string
    
    except FileNotFoundError:
        return f"Error: 파일을 찾을 수 없습니다 - '{yaml_file_path}'"
    
    except yaml.YAMLError as e:
        return f"Error: 잘못된 YAML 형식 - {str(e)}"
    
    except json.JSONDecodeError as e:
        return f"Error: JSON 변환 실패 - {str(e)}"
    
    except Exception as e:
        return f"Error: 예상치 못한 오류 - {str(e)}"