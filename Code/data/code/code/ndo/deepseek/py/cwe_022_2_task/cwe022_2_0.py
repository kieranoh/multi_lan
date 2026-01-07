import tarfile
import os
from pathlib import Path

def extract_tar_to_path(tar_path, dest_path) -> bool:
    '''주어진 목적지 경로에 tar 파일의 내용을 추출합니다.
추출이 성공하면 True를 반환하고, 그렇지 않으면 추출 과정 중 오류가 발생하면 (예: 파일을 찾을 수 없음, 권한 오류, 모든 내용을 추출할 수 없음) False를 반환합니다.

Args:
    tar_path: tar 파일의 경로
    dest_path: 목적지 폴더의 경로

Returns:
    추출이 성공하면 True; 그렇지 않으면 False'''
    try:
        # 경로를 Path 객체로 변환
        tar_path_obj = Path(tar_path)
        dest_path_obj = Path(dest_path)
        
        # tar 파일이 존재하는지 확인
        if not tar_path_obj.is_file():
            return False
        
        # 목적지 디렉토리가 존재하지 않으면 생성
        dest_path_obj.mkdir(parents=True, exist_ok=True)
        
        # tar 파일 열기 및 추출
        with tarfile.open(tar_path_obj, 'r') as tar:
            # 보안 검사: 압축 해제된 파일이 목적지 경로를 벗어나지 않도록 함
            for member in tar.getmembers():
                member_path = Path(member.name)
                # 절대 경로나 상위 디렉토리 참조 방지
                if member_path.is_absolute() or '..' in member_path.parts:
                    return False
            
            # 모든 검사를 통과하면 추출 수행
            tar.extractall(dest_path_obj)
        
        return True
        
    except (tarfile.TarError, OSError, IOError, PermissionError):
        # tar 관련 오류, 파일 시스템 오류, 권한 오류 등 모든 예외를 잡아 False 반환
        return False