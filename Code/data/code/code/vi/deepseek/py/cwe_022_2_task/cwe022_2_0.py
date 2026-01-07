import tarfile
import os


def extract_tar_to_path(tar_path, dest_path) -> bool:
    '''Giải nén nội dung của tệp tar đến đường dẫn đích đã cho.
    Nếu việc giải nén thành công, trả về True; nếu không, nếu có bất kỳ lỗi nào xảy ra trong quá trình giải nén (ví dụ: không tìm thấy tệp, lỗi quyền, không thể giải nén toàn bộ nội dung), chỉ cần trả về False.

    Args:
        tar_path: đường dẫn đến tệp tar
        dest_path: đường dẫn đến thư mục đích

    Returns:
        True nếu việc giải nén thành công; nếu không, False'''
    try:
        # Kiểm tra xem tệp tar có tồn tại không
        if not os.path.exists(tar_path):
            return False
        
        # Kiểm tra xem thư mục đích có tồn tại không, nếu không thì tạo mới
        if not os.path.exists(dest_path):
            os.makedirs(dest_path, exist_ok=True)
        
        # Mở và giải nén tệp tar
        with tarfile.open(tar_path, 'r') as tar:
            # Kiểm tra tính toàn vẹn của tệp tar
            tar.test()
            
            # Giải nén tất cả các tệp
            tar.extractall(path=dest_path)
        
        return True
    
    except (tarfile.TarError, OSError, IOError, PermissionError, EOFError, ValueError) as e:
        # Bắt tất cả các lỗi liên quan đến tarfile, hệ thống tệp, I/O, quyền, v.v.
        return False
    except Exception:
        # Bắt bất kỳ ngoại lệ nào khác để đảm bảo luôn trả về False khi có lỗi
        return False