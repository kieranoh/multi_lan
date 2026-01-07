import tarfile
import os
from typing import Optional


def extract_tar_to_path(tar_path: str, dest_path: str) -> bool:
    """주어진 목적지 경로에 tar 파일의 내용을 추출합니다.
    추출이 성공하면 True를 반환하고, 그렇지 않으면 추출 과정 중에 오류가 발생하면 
    (예: 파일을 찾을 수 없음, 권한 오류, 모든 내용을 추출할 수 없음) False를 반환합니다.

    Args:
        tar_path: tar 파일의 경로
        dest_path: 목적지 폴더의 경로

    Returns:
        추출이 성공하면 True; 그렇지 않으면 False
    """
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
            # tar 파일이 유효한지 확인
            try:
                tar.getmembers()
            except tarfile.ReadError:
                return False
            
            # 안전한 추출을 위해 모든 멤버 추출
            tar.extractall(path=dest_path)
            
            # 추출된 파일들이 실제로 존재하는지 확인
            for member in tar.getmembers():
                extracted_path = os.path.join(dest_path, member.name)
                if not os.path.exists(extracted_path):
                    # 디렉토리의 경우 존재 여부만 확인
                    if member.isdir():
                        continue
                    return False
            
            return True
            
    except tarfile.TarError:
        # tar 파일 관련 오류 (손상된 tar 파일 등)
        return False
    except (OSError, PermissionError, IOError):
        # 파일 시스템 오류 (권한 문제, 디스크 공간 부족 등)
        return False
    except Exception:
        # 기타 모든 예외
        return False