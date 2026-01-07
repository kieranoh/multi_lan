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
    
    # 목적지 디렉토리 생성 시도
    try:
        os.makedirs(dest_path, exist_ok=True)
    except (OSError, PermissionError):
        return False
    
    # tar 파일 추출 시도
    try:
        with tarfile.open(tar_path, 'r') as tar:
            # 안전한 추출을 위한 검증
            for member in tar.getmembers():
                # 악의적인 경로 조작 방지 (디렉토리 순회 공격 방지)
                member_path = os.path.join(dest_path, member.name)
                if not os.path.realpath(member_path).startswith(os.path.realpath(dest_path)):
                    return False
            
            # 모든 검증 통과 후 추출 수행
            tar.extractall(path=dest_path)
        return True
        
    except (tarfile.TarError, OSError, IOError, PermissionError):
        return False
    except Exception:
        # 기타 모든 예외 처리
        return False