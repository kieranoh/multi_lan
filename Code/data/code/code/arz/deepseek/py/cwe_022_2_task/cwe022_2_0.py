import tarfile
import os

def extract_tar_to_path(tar_path, dest_path) -> bool:
    '''주어진 목적지 경로에 tar 파일의 내용을 추출합니다.
추출이 성공하면 True를 반환하고, 그렇지 않으면 추출 과정에서 오류가 발생하면 (예: 파일을 찾을 수 없음, 권한 오류, 모든 내용을 추출할 수 없음) False를 반환합니다.

Args:
    tar_path: tar 파일의 경로
    dest_path: 목적지 폴더의 경로

Returns:
    추출이 성공하면 True; 그렇지 않으면 False'''
    try:
        # 입력 경로 유효성 검사
        if not os.path.exists(tar_path):
            return False
        
        # 목적지 디렉토리가 존재하지 않으면 생성
        if not os.path.exists(dest_path):
            os.makedirs(dest_path, exist_ok=True)
        
        # tar 파일 열기 및 추출
        with tarfile.open(tar_path, 'r') as tar:
            # 보안 검사: 경로 조작 방지
            for member in tar.getmembers():
                member_path = os.path.join(dest_path, member.name)
                if not os.path.realpath(member_path).startswith(os.path.realpath(dest_path)):
                    return False
            
            # 모든 파일 추출
            tar.extractall(path=dest_path)
        
        return True
        
    except (tarfile.TarError, OSError, IOError, PermissionError):
        # tar 관련 오류, 파일 시스템 오류, 권한 오류 등 모든 예외 처리
        return False