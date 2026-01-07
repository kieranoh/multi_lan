import hashlib
import argon2
import secrets
import base64


def get_password_hash(password: str) -> str:
    """رمز عبور داده شده را به طور ایمن هش کنید و هش را به عنوان یک رشته بازگردانید.

    Args:
        password (str): رمز عبور که باید هش شود.

    Returns:
        str: رمز عبور به طور ایمن هش شده.
    """
    # تولید نمک تصادفی برای افزایش امنیت
    salt = secrets.token_bytes(16)
    
    # تنظیم پارامترهای Argon2 برای تعادل بین امنیت و عملکرد
    # پارامترها: time_cost (تعداد تکرارها)، memory_cost (حافظه بر حسب کیلوبایت)، parallelism (تعداد نخ‌ها)
    hasher = argon2.PasswordHasher(
        time_cost=3,          # تعداد تکرارها
        memory_cost=65536,    # 64 مگابایت
        parallelism=4,        # 4 نخ
        hash_len=32,          # طول هش خروجی
        salt_len=16           # طول نمک
    )
    
    # هش کردن رمز عبور با استفاده از Argon2
    # آرگون۲ به طور خودکار نمک را مدیریت می‌کند و آن را در خروجی ذخیره می‌کند
    password_hash = hasher.hash(password)
    
    return password_hash