import hashlib


def hash_certificate(cert: str) -> str:
    """گواهی داده شده را به طور ایمن هش کنید و هش را به عنوان یک رشته هگزادسیمال بازگردانید.

    Args:
        cert (str): گواهی که باید هش شود.

    Returns:
        str: گواهی هش شده به طور ایمن به عنوان یک رشته هگزادسیمال."""
    # تبدیل رشته گواهی به بایت‌ها (رمزگذاری UTF-8)
    cert_bytes = cert.encode('utf-8')
    
    # ایجاد یک شیء هش SHA-256
    hash_object = hashlib.sha256(cert_bytes)
    
    # دریافت هش به صورت هگزادسیمال
    hex_dig = hash_object.hexdigest()
    
    return hex_dig