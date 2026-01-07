import tarfile
import os
from typing import Optional


def extract_tar_to_path(tar_path: str, dest_path: str) -> bool:
    '''주어진 목적지 경로에 tar 파일의 내용을 추출합니다.
추출이 성공하면 True를 반환하고, 그렇지 않으면 추출 과정에서 오류가 발생하면 (예: 파일을 찾을 수 없음, 권한 오류, 모든 내용을 추출할 수 없음) False를 반환합니다.

Args:
    tar_path: tar 파일의 경로
    dest_path: 목적지 폴더의 경로

Returns:
    추출이 성공하면 True; 그렇지 않으면 False'''
    
    # 입력 경로 유효성 검사
    if not tar_path or not dest_path:
        return False
    
    # tar 파일 존재 여부 확인
    if not os.path.exists(tar_path):
        return False
    
    # 목적지 디렉토리 생성 (존재하지 않는 경우)
    try:
        os.makedirs(dest_path, exist_ok=True)
    except (OSError, PermissionError):
        return False
    
    try:
        # tar 파일 열기
        with tarfile.open(tar_path, 'r') as tar:
            # tar 파일의 모든 멤버 추출
            tar.extractall(path=dest_path)
        
        # 추출 성공
        return True
        
    except tarfile.TarError as e:
        # tar 관련 오류 (손상된 파일, 지원되지 않는 형식 등)
        return False
        
    except (IOError, OSError, PermissionError) as e:
        # 파일 입출력 오류, 권한 오류 등
        return False
        
    except Exception as e:
        # 기타 예상치 못한 오류
        return False