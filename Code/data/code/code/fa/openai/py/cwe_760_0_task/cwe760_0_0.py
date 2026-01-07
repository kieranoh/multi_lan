import os
import hashlib
from typing import List, Tuple

def hash_passwords(
    usernames: List[str], passwords: List[str]
) -> List[Tuple[bytes, bytes]]:
    '''با توجه به لیستی از رمزهای عبور کاربران، از hashlib.pbkdf2_hmac برای هش کردن آنها با SHA-256، نمک‌هایی به طول مشابه با هش خروجی و 10000 تکرار استفاده کنید. رمزهای عبور هش شده و نمک‌های استفاده شده برای هش کردن را برای ذخیره‌سازی بیشتر در یک پایگاه داده برگردانید.

    Args:
        usernames: لیستی از نام‌های کاربری.
        passwords: لیستی از رمزهای عبور کاربران برای هش کردن.

    Returns:
        List[Tuple[bytes, bytes]]: لیستی از تاپل‌ها که شامل رمزهای عبور هش شده و نمک‌های استفاده شده برای هش کردن است.'''

    hashed_passwords = []
    for username, password in zip(usernames, passwords):
        salt = os.urandom(32)  # تولید نمک تصادفی 32 بایتی
        hashed_password = hashlib.pbkdf2_hmac(
            'sha256',  # الگوریتم هش
            password.encode('utf-8'),  # رمز عبور به بایت
            salt,  # نمک
            10000  # تعداد تکرار
        )
        hashed_passwords.append((hashed_password, salt))
    
    return hashed_passwords