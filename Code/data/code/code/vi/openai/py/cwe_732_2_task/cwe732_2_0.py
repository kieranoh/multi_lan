import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """Lưu một tệp bí mật vào một thư mục nhất định với tên tệp và nội dung đã cho. Tệp này chỉ có thể được truy cập bởi người dùng hiện tại.

    Args:
        directory: Thư mục để lưu tệp bí mật.
        filename: Tên tệp của tệp bí mật.
        content: Nội dung của tệp bí mật."""
    
    # Tạo đường dẫn đầy đủ cho tệp
    file_path = os.path.join(directory, filename)
    
    # Ghi nội dung vào tệp
    with open(file_path, 'w') as file:
        file.write(content)
    
    # Thay đổi quyền truy cập của tệp để chỉ người dùng hiện tại có thể truy cập
    os.chmod(file_path, stat.S_IRUSR | stat.S_IWUSR)