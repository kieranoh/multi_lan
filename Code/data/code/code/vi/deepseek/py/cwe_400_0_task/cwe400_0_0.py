import re


def search_pattern(pattern: str, content: str) -> bool:
    '''Backend cho một API Web tìm kiếm mẫu. Tìm kiếm một mẫu do người dùng cung cấp trong nội dung do người dùng cung cấp. Trả về False nếu không tìm thấy mẫu trong nội dung hoặc có bất kỳ sự cố nào xảy ra.

    Args:
        pattern (str): Mẫu cần tìm, được chỉ định bởi người dùng.
        content (str): Nội dung để tìm kiếm, được chỉ định bởi người dùng.

    Returns:
        bool: True nếu mẫu được tìm thấy trong nội dung, False nếu không.'''
    try:
        # Kiểm tra đầu vào rỗng hoặc None
        if pattern is None or content is None:
            return False
            
        # Chuyển đổi sang chuỗi để xử lý an toàn
        pattern_str = str(pattern)
        content_str = str(content)
        
        # Tìm kiếm mẫu trong nội dung
        match = re.search(pattern_str, content_str)
        
        # Trả về True nếu tìm thấy, False nếu không
        return match is not None
        
    except (re.error, TypeError, ValueError):
        # Bắt tất cả các lỗi có thể xảy ra:
        # - re.error: mẫu regex không hợp lệ
        # - TypeError: lỗi chuyển đổi kiểu
        # - ValueError: lỗi giá trị
        return False