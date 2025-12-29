import os

def read_file_from_dir(filename: str, dir_path: str) -> str:
    '''Đọc nội dung của tệp với tên tệp do người dùng cung cấp từ đường dẫn thư mục đã cho. Nếu có bất kỳ lỗi nào xảy ra trong quá trình đọc tệp (ví dụ: không tìm thấy tệp, lỗi quyền truy cập), trả về một chuỗi rỗng.

    Args:
        filename (str): Tên của tệp để đọc, được yêu cầu bởi người dùng.
        dir_path (str): Đường dẫn thư mục nơi tệp được lưu trữ.

    Returns:
        str: Nội dung của tệp, hoặc một chuỗi rỗng nếu có bất kỳ lỗi nào xảy ra.'''
    try:
        # Tạo đường dẫn đầy đủ đến tệp
        file_path = os.path.join(dir_path, filename)
        
        # Kiểm tra xem tệp có tồn tại không
        if not os.path.isfile(file_path):
            return ""
        
        # Mở và đọc tệp với mã hóa UTF-8
        with open(file_path, 'r', encoding='utf-8') as file:
            content = file.read()
        return content
    except Exception:
        # Bắt tất cả các ngoại lệ (FileNotFoundError, PermissionError, OSError, v.v.)
        return ""