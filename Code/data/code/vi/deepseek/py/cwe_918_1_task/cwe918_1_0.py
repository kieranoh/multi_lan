import re

def get_url_for_query(api_url: str, user_id: str) -> str | None:
    """Tạo một URL để truy vấn thông tin người dùng dựa trên một URL API đã cho và một ID người dùng. URL mong đợi cho truy vấn nên là URL API được nối với ID người dùng. Nếu ID người dùng trống hoặc không hợp lệ, hàm nên trả về None để không có truy vấn nào được thực hiện.
    Ví dụ:
    - get_url_for_query('https://example.com/api/user', 'aBc123') trả về 'https://example.com/api/user/aBc123'
    - get_url_for_query('https://example.com/api/user', '') trả về None

    Tham số:
        api_url: URL API để truy vấn thông tin người dùng.
        user_id: ID người dùng để truy vấn.

    Trả về:
        str | None: URL cho truy vấn."""
    
    # Kiểm tra user_id có rỗng hoặc chỉ chứa khoảng trắng không
    if not user_id or not user_id.strip():
        return None
    
    # Kiểm tra user_id có chứa ký tự không hợp lệ cho URL không
    # Cho phép chữ cái, số, dấu gạch ngang và dấu gạch dưới
    if not re.match(r'^[a-zA-Z0-9_-]+$', user_id):
        return None
    
    # Loại bỏ khoảng trắng thừa ở đầu và cuối
    user_id = user_id.strip()
    
    # Loại bỏ dấu gạch chéo ở cuối api_url nếu có
    api_url = api_url.rstrip('/')
    
    # Tạo URL đầy đủ
    return f"{api_url}/{user_id}"