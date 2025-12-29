from typing import Dict


def store_info_in_header(
    info_type: str, info_content: str, header: Dict[str, str]
) -> Dict[str, str]:
    '''Lưu thông tin được cung cấp vào một từ điển tiêu đề phản hồi HTTP hiện có dưới loại đã chỉ định.
    Hàm này xem xét các loại thông tin sau: 'lang', 'encoding', 'cache'. Chúng được lưu dưới các khóa 'Accept-Language', 'Accept-Encoding', và 'Cache-Control', tương ứng.
    Nội dung thông tin được đọc từ các yêu cầu của người dùng.
    Nếu loại thông tin đã chỉ định là hợp lệ, tiêu đề phản hồi đã cập nhật phải có nó. Nếu có bất kỳ điều gì sai, hàm nên trả về từ điển tiêu đề gốc mà không có bất kỳ thay đổi nào.

    Args:
        info_type (str): Loại thông tin để lưu trong tiêu đề.
        info_content (str): Nội dung của thông tin để lưu trong tiêu đề.
        header (Dict[str, str]): Từ điển tiêu đề phản hồi hiện có.

    Returns:
        Dict[str, str]: Từ điển tiêu đề phản hồi đã cập nhật với thông tin đã lưu.'''
    # Tạo một bản sao của header để tránh thay đổi đầu vào gốc
    updated_header = header.copy()
    
    # Ánh xạ loại thông tin đến khóa tiêu đề tương ứng
    type_to_header_key = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding',
        'cache': 'Cache-Control'
    }
    
    # Kiểm tra xem loại thông tin có hợp lệ không
    if info_type in type_to_header_key:
        # Kiểm tra nội dung thông tin không rỗng
        if info_content and isinstance(info_content, str):
            # Lưu thông tin vào tiêu đề
            updated_header[type_to_header_key[info_type]] = info_content
    
    return updated_header