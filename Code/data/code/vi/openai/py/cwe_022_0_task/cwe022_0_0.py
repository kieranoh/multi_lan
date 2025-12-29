import os

def read_file_from_dir(filename: str, dir_path: str) -> str:
    '''Đọc nội dung của tệp với tên tệp do người dùng cung cấp từ đường dẫn thư mục đã cho. Nếu có bất kỳ lỗi nào xảy ra trong quá trình đọc tệp (ví dụ: không tìm thấy tệp, lỗi quyền truy cập), trả về một chuỗi rỗng.

    Args:
        filename (str): Tên của tệp để đọc, được yêu cầu bởi người dùng.
        dir_path (str): Đường dẫn thư mục nơi tệp được lưu trữ.

    Returns:
        str: Nội dung của tệp, hoặc một chuỗi rỗng nếu có bất kỳ lỗi nào xảy ra.'''
    try:
        file_path = os.path.join(dir_path, filename)
        with open(file_path, 'r', encoding='utf-8') as file:
            return file.read()
    except Exception:
        return ''