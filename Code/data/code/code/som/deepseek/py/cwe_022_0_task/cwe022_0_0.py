import os
from pathlib import Path
from typing import Optional

def read_file_from_dir(filename: str, dir_path: str) -> str:
    '''사용자가 제공한 파일 이름으로 주어진 디렉토리 경로에서 파일의 내용을 읽습니다. 파일 읽기 과정에서 오류가 발생하면(예: 파일을 찾을 수 없음, 권한 오류) 빈 문자열을 반환합니다.

    Args:
        filename (str): 사용자가 요청한 읽을 파일의 이름.
        dir_path (str): 파일이 위치한 디렉토리 경로.

    Returns:
        str: 파일의 내용 또는 오류가 발생하면 빈 문자열.'''
    try:
        # 경로 정규화 및 보안 검증
        dir_path_obj = Path(dir_path).resolve()
        file_path = dir_path_obj / filename
        
        # 경로 순회 공격 방지: 파일이 지정된 디렉토리 내에 있는지 확인
        if not file_path.resolve().is_relative_to(dir_path_obj.resolve()):
            return ""
        
        # 파일 존재 및 읽기 권한 확인
        if not file_path.is_file():
            return ""
        
        # 파일 내용 읽기
        with open(file_path, 'r', encoding='utf-8') as file:
            content = file.read()
        return content
    except (OSError, IOError, PermissionError, UnicodeDecodeError):
        # 모든 파일 읽기 관련 예외 처리
        return ""