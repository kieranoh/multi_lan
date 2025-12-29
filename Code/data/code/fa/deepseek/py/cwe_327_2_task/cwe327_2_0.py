from typing import Tuple
from Crypto.Cipher import AES, DES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''داده‌ها را با کلید با استفاده از حالت CBC رمزگذاری کنید.
کلید ارائه شده به اندازه کافی طولانی است (>= 64 بایت) برای تمام الگوریتم‌های موجود. فقط یک الگوریتم را برای پیاده‌سازی انتخاب کنید و پیشوند بایت‌های کلید ارائه شده را که با طول مورد نیاز مطابقت دارد، استفاده کنید. بر اساس طول کلید، الگوریتم را انتخاب نکنید.
داده‌های رمزگذاری شده، IV (بردار اولیه) و کلید استفاده شده برای رمزگذاری را برگردانید.

    Args:
        key (bytes): بایت‌ها برای تولید کلید رمزگذاری.
        data (bytes): داده‌ها برای رمزگذاری.

    Returns:
        Tuple[bytes, bytes, bytes]: داده‌های رمزگذاری شده، IV و کلید استفاده شده برای رمزگذاری.'''
    # انتخاب الگوریتم AES (با توجه به اینکه کلید به اندازه کافی طولانی است)
    # استفاده از 16 بایت اول کلید برای کلید AES-128
    key_length = 16  # AES-128
    encryption_key = key[:key_length]
    
    # تولید IV تصادفی
    iv = get_random_bytes(16)  # IV 16 بایتی برای AES
    
    # ایجاد شیء رمزگذار AES در حالت CBC
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)
    
    # اضافه کردن padding به داده‌ها و رمزگذاری
    padded_data = pad(data, AES.block_size)
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, encryption_key