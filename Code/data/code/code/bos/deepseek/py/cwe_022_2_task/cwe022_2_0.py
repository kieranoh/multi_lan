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
    try:
        # 입력 경로 유효성 검사
        if not tar_path or not dest_path:
            return False
        
        # 경로를 Path 객체로 변환
        tar_file = Path(tar_path)
        dest_dir = Path(dest_path)
        
        # tar 파일 존재 여부 확인
        if not tar_file.exists() or not tar_file.is_file():
            return False
        
        # 목적지 디렉토리 생성 (존재하지 않는 경우)
        dest_dir.mkdir(parents=True, exist_ok=True)
        
        # tar 파일 열기 및 추출
        with tarfile.open(tar_file, 'r') as tar:
            # 보안 검사: 악의적인 경로 조작 방지
            for member in tar.getmembers():
                member_path = Path(member.name)
                # 절대 경로나 상위 디렉토리 참조 방지
                if member_path.is_absolute() or '..' in member_path.parts:
                    return False
            
            # 안전하게 모든 파일 추출
            tar.extractall(path=dest_dir)
        
        return True
        
    except (tarfile.TarError, OSError, IOError, PermissionError, ValueError) as e:
        # 모든 관련 예외 처리
        return False
    except Exception:
        # 기타 모든 예외 처리
        return False