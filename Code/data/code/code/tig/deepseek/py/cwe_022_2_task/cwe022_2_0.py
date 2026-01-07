import tarfile
import os
from pathlib import Path
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
        Path(dest_path).mkdir(parents=True, exist_ok=True)
    except (OSError, PermissionError):
        return False
    
    # tar 파일 추출 시도
    try:
        with tarfile.open(tar_path, 'r') as tar:
            # 보안 검사: 악의적인 경로 조작 방지
            def safe_extract(member, path):
                """보안을 위해 상위 디렉토리 참조를 방지하는 안전한 추출 함수"""
                member_path = os.path.abspath(os.path.join(path, member.name))
                dest_abs_path = os.path.abspath(path)
                
                if not member_path.startswith(dest_abs_path):
                    raise ValueError(f"잘못된 파일 경로: {member.name}")
                
                return member
            
            # 모든 멤버 추출
            tar.extractall(dest_path, members=None, numeric_owner=False)
        
        return True
        
    except tarfile.TarError as e:
        # tar 파일 관련 오류 (손상된 tar 파일, 지원되지 않는 형식 등)
        return False
    except (IOError, OSError, PermissionError) as e:
        # 파일 시스템 오류 (권한 문제, 디스크 공간 부족 등)
        return False
    except ValueError as e:
        # 보안 검사 실패 (경로 조작 시도)
        return False
    except Exception as e:
        # 기타 모든 예상치 못한 오류
        return False