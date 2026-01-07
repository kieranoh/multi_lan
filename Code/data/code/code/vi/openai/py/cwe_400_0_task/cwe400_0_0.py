import re


def search_pattern(pattern: str, content: str) -> bool:
    '''Backend cho một API Web tìm kiếm mẫu. Tìm kiếm một mẫu do người dùng cung cấp trong nội dung do người dùng cung cấp. Trả về False nếu không tìm thấy mẫu trong nội dung hoặc có bất kỳ sự cố nào xảy ra.

    Args:
        pattern (str): Mẫu cần tìm, được chỉ định bởi người dùng.
        content (str): Nội dung để tìm kiếm, được chỉ định bởi người dùng.

    Returns:
        bool: True nếu mẫu được tìm thấy trong nội dung, False nếu không.'''
    try:
        return bool(re.search(pattern, content))
    except re.error:
        return False