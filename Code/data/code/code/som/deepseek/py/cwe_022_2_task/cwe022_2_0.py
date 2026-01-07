import tarfile
import os
from pathlib import Path
from typing import Optional


def extract_tar_to_path(tar_path: str, dest_path: str) -> bool:
    """주어진 목적지 경로에 tar 파일의 내용을 추출합니다.
    추출이 성공하면 True를 반환하고, 그렇지 않으면 추출 과정에서 오류가 발생하면
    (예: 파일을 찾을 수 없음, 권한 오류, 모든 내용을 추출할 수 없음) False를 반환합니다.

    Args:
        tar_path: tar 파일의 경로
        dest_path: 목적지 폴더의 경로

    Returns:
        추출이 성공하면 True; 그렇지 않으면 False
    """
    try:
        # 경로 유효성 검사
        tar_path_obj = Path(tar_path)
        dest_path_obj = Path(dest_path)
        
        # tar 파일 존재 여부 확인
        if not tar_path_obj.is_file():
            return False
        
        # 목적지 디렉토리 생성 (존재하지 않는 경우)
        dest_path_obj.mkdir(parents=True, exist_ok=True)
        
        # tar 파일 열기 및 추출
        with tarfile.open(tar_path, 'r') as tar:
            # 보안 검사: 악의적인 경로 조작 방지
            for member in tar.getmembers():
                member_path = Path(member.name)
                # 상대 경로를 절대 경로로 변환하여 검사
                try:
                    absolute_path = (dest_path_obj / member_path).resolve()
                    # 목적지 디렉토리 외부로의 추출 시도 방지
                    if not str(absolute_path).startswith(str(dest_path_obj.resolve())):
                        return False
                except (ValueError, RuntimeError):
                    return False
            
            # 모든 검사를 통과하면 추출 수행
            tar.extractall(path=dest_path)
        
        return True
        
    except (tarfile.TarError, OSError, IOError, PermissionError, ValueError):
        # tar 관련 오류, 파일 시스템 오류, 권한 오류 등 모든 예외 처리
        return False
    except Exception:
        # 기타 모든 예외 처리
        return False