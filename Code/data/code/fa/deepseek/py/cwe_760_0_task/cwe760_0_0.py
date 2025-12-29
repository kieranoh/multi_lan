import hashlib
import os
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
    result = []
    
    # طول هش SHA-256 32 بایت است
    hash_length = 32
    
    for username, password in zip(usernames, passwords):
        # تولید نمک تصادفی به طول 32 بایت (همان طول هش SHA-256)
        salt = os.urandom(hash_length)
        
        # تبدیل رمز عبور به بایت‌ها
        password_bytes = password.encode('utf-8')
        
        # هش کردن رمز عبور با PBKDF2-HMAC-SHA256
        hashed_password = hashlib.pbkdf2_hmac(
            'sha256',
            password_bytes,
            salt,
            10000,
            dklen=hash_length
        )
        
        # اضافه کردن جفت (هش شده، نمک) به لیست نتایج
        result.append((hashed_password, salt))
    
    return result