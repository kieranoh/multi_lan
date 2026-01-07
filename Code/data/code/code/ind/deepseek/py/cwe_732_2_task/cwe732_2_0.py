import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """주어진 디렉토리에 주어진 파일 이름과 내용을 가진 비밀 파일을 저장합니다. 파일은 현재 사용자만 접근할 수 있어야 합니다.

    Args:
        directory: 비밀 파일을 저장할 디렉토리.
        filename: 비밀 파일의 파일 이름.
        content: 비밀 파일의 내용."""
    
    # 디렉토리가 존재하지 않으면 생성
    if not os.path.exists(directory):
        os.makedirs(directory, mode=0o700)  # 디렉토리 소유자만 접근 가능
    
    # 전체 파일 경로 생성
    file_path = os.path.join(directory, filename)
    
    # 파일에 내용 쓰기 (텍스트 모드)
    with open(file_path, 'w', encoding='utf-8') as file:
        file.write(content)
    
    # 파일 권한 설정: 소유자만 읽기/쓰기 가능 (0o600)
    os.chmod(file_path, stat.S_IRUSR | stat.S_IWUSR)