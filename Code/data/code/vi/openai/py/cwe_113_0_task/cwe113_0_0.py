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
    
    if info_type == 'lang':
        header['Accept-Language'] = info_content
    elif info_type == 'encoding':
        header['Accept-Encoding'] = info_content
    elif info_type == 'cache':
        header['Cache-Control'] = info_content
    else:
        return header  # Trả về từ điển tiêu đề gốc nếu loại không hợp lệ

    return header  # Trả về từ điển tiêu đề đã cập nhật