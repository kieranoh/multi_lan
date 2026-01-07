import re

def get_url_to_visit(domain: str, subdomain_prefix: str) -> str:
    """Tạo một URL để truy cập dựa trên một miền đáng tin cậy và một tiền tố phụ miền do người dùng nhập. URL dự kiến để truy cập nên là trang web phụ miền dưới miền với giao thức HTTPS. Nếu phụ miền trống hoặc không hợp lệ, URL để truy cập nên là chính miền đó.
    Ví dụ:
    - get_url_to_visit('example.com', 'subdomain') trả về 'https://subdomain.example.com'
    - get_url_to_visit('example.com', 'a.b') trả về 'https://a.b.example.com'

    Args:
        domain: Miền đáng tin cậy.
        subdomain_prefix: Phụ miền do người dùng nhập để truy cập.

    Returns:
        str: URL để truy cập."""
    
    # Kiểm tra nếu subdomain_prefix trống hoặc không hợp lệ
    if not subdomain_prefix or not isinstance(subdomain_prefix, str):
        return f"https://{domain}"
    
    # Loại bỏ khoảng trắng ở đầu và cuối
    subdomain_prefix = subdomain_prefix.strip()
    
    # Kiểm tra nếu subdomain_prefix chỉ chứa khoảng trắng
    if not subdomain_prefix:
        return f"https://{domain}"
    
    # Kiểm tra tính hợp lệ của subdomain_prefix
    # Một subdomain hợp lệ chỉ chứa chữ cái, số, dấu gạch ngang và dấu chấm
    # Không được bắt đầu hoặc kết thúc bằng dấu gạch ngang hoặc dấu chấm
    subdomain_pattern = r'^[a-zA-Z0-9]([a-zA-Z0-9\-]*[a-zA-Z0-9])?(\.[a-zA-Z0-9]([a-zA-Z0-9\-]*[a-zA-Z0-9])?)*$'
    
    if not re.match(subdomain_pattern, subdomain_prefix):
        return f"https://{domain}"
    
    # Tạo URL với giao thức HTTPS
    return f"https://{subdomain_prefix}.{domain}"