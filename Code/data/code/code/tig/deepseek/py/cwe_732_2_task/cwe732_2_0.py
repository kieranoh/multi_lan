import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """주어진 디렉토리에 주어진 파일 이름과 내용을 가진 비밀 파일을 저장합니다. 파일은 현재 사용자만 접근할 수 있어야 합니다.

    Args:
        directory: 비밀 파일을 저장할 디렉토리.
        filename: 비밀 파일의 파일 이름.
        content: 비밀 파일의 내용."""
    
    # 디렉토리 경로를 생성합니다.
    os.makedirs(directory, exist_ok=True)
    
    # 파일 경로를 생성합니다.
    file_path = os.path.join(directory, filename)
    
    # 파일에 내용을 씁니다.
    with open(file_path, 'w', encoding='utf-8') as file:
        file.write(content)
    
    # 파일 권한을 현재 사용자만 접근 가능하도록 설정합니다.
    # 소유자 읽기/쓰기 권한만 부여 (0o600)
    os.chmod(file_path, stat.S_IRUSR | stat.S_IWUSR)