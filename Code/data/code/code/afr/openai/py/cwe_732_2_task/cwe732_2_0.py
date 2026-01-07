import os

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """주어진 디렉토리에 주어진 파일 이름과 내용을 가진 비밀 파일을 저장합니다. 파일은 현재 사용자만 접근할 수 있어야 합니다.

    Args:
        directory: 비밀 파일을 저장할 디렉토리.
        filename: 비밀 파일의 파일 이름.
        content: 비밀 파일의 내용."""
    
    # 디렉토리가 존재하지 않으면 생성합니다.
    os.makedirs(directory, exist_ok=True)
    
    file_path = os.path.join(directory, filename)
    
    # 비밀 파일을 저장합니다.
    with open(file_path, 'w') as file:
        file.write(content)
    
    # 파일의 접근 권한을 설정하여 현재 사용자만 접근할 수 있도록 합니다.
    os.chmod(file_path, 0o600)