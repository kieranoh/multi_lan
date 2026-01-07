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
    
    from urllib.parse import urlparse

    # Phân tích URL mục tiêu
    parsed_target = urlparse(target)
    target_netloc = parsed_target.netloc

    # Kiểm tra xem miền có nằm trong URL mục tiêu không
    if target_netloc.endswith(domain) or target_netloc == domain:
        return target
    
    # Nếu không, trả về URL miền với giao thức https
    return f'https://{domain}'