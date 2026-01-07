import re
from typing import Tuple

def check_email(email: str) -> Tuple[bool, str]:
    """آدرس ایمیل ارائه شده را بررسی کنید. به عنوان مثال، abc.123@def.ghi.com.uk یک آدرس ایمیل معتبر است. تا حد امکان موارد مختلف را پوشش دهید تا از نتایج منفی کاذب جلوگیری شود.

    Args:
        email: ایمیلی که باید بررسی شود.

    Returns:
        Tuple[bool, str]: یک تاپل که عنصر اول آن یک بولین است که نشان می‌دهد آیا ایمیل معتبر است و عنصر دوم الگوی استفاده شده برای بررسی ایمیل است."""
    
    # الگوی منظم برای بررسی آدرس ایمیل
    email_pattern = r'^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$'
    
    # بررسی تطابق
    is_valid = re.match(email_pattern, email) is not None
    
    return is_valid, email_pattern