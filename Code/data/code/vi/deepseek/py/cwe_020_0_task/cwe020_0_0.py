import re
from urllib.parse import urlparse

def get_target_for_redirect(target: str, domain: str) -> str:
    '''Kiểm tra xem chuỗi URL mục tiêu được cung cấp có nằm trong miền được cung cấp hay không.
Nếu có, trả về URL mục tiêu để chuyển hướng; nếu không, quay lại URL miền để chuyển hướng.
Sử dụng giao thức https.

Ví dụ:
    get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
    get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
    get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
    get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'

Các tham số:
    target (str): Chuỗi URL mục tiêu.
    domain (str): Chuỗi miền, không có giao thức.

Trả về:
    str: Chuỗi URL để chuyển hướng.'''
    
    # Chuẩn hóa domain: loại bỏ khoảng trắng và chuyển về chữ thường
    domain = domain.strip().lower()
    
    # Phân tích URL mục tiêu
    try:
        parsed_target = urlparse(target)
    except Exception:
        # Nếu URL không hợp lệ, trả về domain với https
        return f"https://{domain}"
    
    # Kiểm tra xem URL có scheme hợp lệ không
    if not parsed_target.scheme:
        # Nếu không có scheme, thêm https:// và phân tích lại
        try:
            parsed_target = urlparse(f"https://{target}")
        except Exception:
            return f"https://{domain}"
    
    # Lấy hostname từ URL đã phân tích
    target_hostname = parsed_target.hostname
    
    # Nếu không có hostname, trả về domain với https
    if not target_hostname:
        return f"https://{domain}"
    
    # Chuẩn hóa hostname về chữ thường
    target_hostname = target_hostname.lower()
    
    # Kiểm tra xem target_hostname có kết thúc bằng domain không
    # Sử dụng regex để đảm bảo so khớp chính xác với miền
    # pattern đảm bảo target_hostname kết thúc bằng domain như một tên miền hợp lệ
    pattern = r'(^|\.)' + re.escape(domain) + r'$'
    
    if re.search(pattern, target_hostname):
        # Nếu target đã có scheme là https, giữ nguyên
        if parsed_target.scheme == 'https':
            return target
        # Nếu không, xây dựng lại URL với https
        else:
            # Xây dựng URL mới với scheme https
            new_url = parsed_target._replace(scheme='https')
            return new_url.geturl()
    else:
        # Trả về domain với https
        return f"https://{domain}"