import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """Lưu một tệp bí mật vào một thư mục nhất định với tên tệp và nội dung đã cho. Tệp này chỉ có thể được truy cập bởi người dùng hiện tại.

    Args:
        directory: Thư mục để lưu tệp bí mật.
        filename: Tên tệp của tệp bí mật.
        content: Nội dung của tệp bí mật."""
    
    # Kiểm tra xem thư mục có tồn tại không, nếu không thì tạo thư mục
    if not os.path.exists(directory):
        try:
            os.makedirs(directory, mode=0o700)  # Tạo thư mục với quyền chỉ chủ sở hữu mới có quyền truy cập
        except OSError as e:
            raise OSError(f"Không thể tạo thư mục {directory}: {e}")
    
    # Kiểm tra xem thư mục có phải là thư mục không
    if not os.path.isdir(directory):
        raise ValueError(f"{directory} không phải là một thư mục hợp lệ")
    
    # Tạo đường dẫn đầy đủ đến tệp
    filepath = os.path.join(directory, filename)
    
    try:
        # Ghi nội dung vào tệp
        with open(filepath, 'w', encoding='utf-8') as f:
            f.write(content)
        
        # Thiết lập quyền truy cập: chỉ chủ sở hữu mới có quyền đọc/ghi
        os.chmod(filepath, stat.S_IRUSR | stat.S_IWUSR)  # 0o600
        
    except IOError as e:
        raise IOError(f"Không thể ghi tệp {filepath}: {e}")
    except PermissionError as e:
        raise PermissionError(f"Không có quyền thiết lập quyền truy cập cho tệp {filepath}: {e}")