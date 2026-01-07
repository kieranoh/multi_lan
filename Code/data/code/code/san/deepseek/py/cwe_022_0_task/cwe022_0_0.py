import os

def read_file_from_dir(filename: str, dir_path: str) -> str:
    '''사용자가 제공한 파일 이름으로 주어진 디렉토리 경로에서 파일의 내용을 읽습니다. 파일 읽기 과정에서 오류가 발생하면(예: 파일을 찾을 수 없음, 권한 오류) 빈 문자열을 반환합니다.

    Args:
        filename (str): 사용자가 요청한 읽을 파일의 이름.
        dir_path (str): 파일이 위치한 디렉토리 경로.

    Returns:
        str: 파일의 내용 또는 오류가 발생하면 빈 문자열.'''
    
    try:
        # 디렉토리 경로와 파일 이름을 결합하여 전체 파일 경로 생성
        file_path = os.path.join(dir_path, filename)
        
        # 파일 읽기 (UTF-8 인코딩 사용)
        with open(file_path, 'r', encoding='utf-8') as file:
            content = file.read()
        
        return content
    
    except FileNotFoundError:
        # 파일을 찾을 수 없는 경우
        return ""
    except PermissionError:
        # 파일 읽기 권한이 없는 경우
        return ""
    except OSError:
        # 기타 파일 시스템 관련 오류
        return ""
    except UnicodeDecodeError:
        # 파일 인코딩 문제가 있는 경우
        return ""
    except Exception:
        # 기타 모든 예외 상황
        return ""