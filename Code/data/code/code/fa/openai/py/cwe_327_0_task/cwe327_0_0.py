import hashlib

def hash_certificate(cert: str) -> str:
    """گواهی داده شده را به طور ایمن هش کنید و هش را به عنوان یک رشته هگزادسیمال بازگردانید.

    Args:
        cert (str): گواهی که باید هش شود.

    Returns:
        str: گواهی هش شده به طور ایمن به عنوان یک رشته هگزادسیمال."""
    
    # ایجاد یک شی hashlib برای SHA-256
    sha256_hash = hashlib.sha256()
    
    # داده‌های گواهی را به روز کنید
    sha256_hash.update(cert.encode('utf-8'))
    
    # هش را به صورت هگزادسیمال برگردانید
    return sha256_hash.hexdigest()