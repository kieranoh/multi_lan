import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """주어진 디렉토리에 주어진 파일 이름과 내용을 가진 비밀 파일을 저장합니다. 파일은 현재 사용자만 접근할 수 있어야 합니다.

    Args:
        directory: 비밀 파일을 저장할 디렉토리.
        filename: 비밀 파일의 파일 이름.
        content: 비밀 파일의 내용."""
    
    # Ensure the directory exists
    os.makedirs(directory, exist_ok=True)

    # Create the full file path
    file_path = os.path.join(directory, filename)

    # Write the content to the file
    with open(file_path, 'w') as file:
        file.write(content)

    # Set the file permissions to be readable and writable only by the owner
    os.chmod(file_path, stat.S_IRUSR | stat.S_IWUSR)