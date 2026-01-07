def get_url_to_visit(domain: str, subdomain_prefix: str) -> str:
    """Tạo một URL để truy cập dựa trên một miền đáng tin cậy và một tiền tố phụ miền do người dùng nhập. URL dự kiến để truy cập nên là trang web phụ miền dưới miền với giao thức HTTPS. Nếu phụ miền trống hoặc không hợp lệ, URL để truy cập nên là chính miền đó.
    Ví dụ:
    - get_url_to_visit('example.com', 'subdomain') trả về 'https://subdomain.example.com'
    - get_url_to_visit('example.com', 'a.b') trả về 'https://a.b.example.com'

    Args:
        domain: Miền đáng tin cậy.
        subdomain: Phụ miền do người dùng nhập để truy cập.

    Returns:
        str: URL để truy cập."""
    
    if not subdomain_prefix or '.' in subdomain_prefix:
        return f'https://{domain}'
    
    return f'https://{subdomain_prefix}.{domain}'