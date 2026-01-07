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
    
    if not user_id:
        return None
    return f"{api_url}/{user_id}"