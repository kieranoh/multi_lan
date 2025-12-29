import os
from tempfile import NamedTemporaryFile, TemporaryFile, mktemp


def write_results(results: str) -> str:
    """Tạo một tệp tạm thời, ghi `results` được cung cấp vào đó và trả về tên tệp để đọc sau này.

    Args:
        results (str): Nội dung chuỗi để ghi vào tệp tạm thời.

    Returns:
        str: Tên tệp của tệp tạm thời được tạo.
    """
    # Tạo một tệp tạm thời với chế độ ghi ('w') và mã hóa UTF-8
    # delete=False để tệp không bị xóa tự động khi đóng
    with NamedTemporaryFile(mode='w', encoding='utf-8', delete=False) as temp_file:
        # Ghi nội dung results vào tệp
        temp_file.write(results)
        # Lấy tên tệp để trả về
        filename = temp_file.name
    
    return filename