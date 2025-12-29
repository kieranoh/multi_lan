from typing import Tuple
from Crypto.Cipher import AES
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
    
    # انتخاب کلید مناسب برای AES (16, 24 یا 32 بایت)
    key_length = len(key)
    if key_length >= 32:
        cipher_key = key[:32]
    elif key_length >= 24:
        cipher_key = key[:24]
    else:
        cipher_key = key[:16]

    # تولید IV
    iv = get_random_bytes(16)

    # ایجاد شیء رمزگذار
    cipher = AES.new(cipher_key, AES.MODE_CBC, iv)

    # رمزگذاری داده‌ها
    encrypted_data = cipher.encrypt(pad(data, AES.block_size))

    return encrypted_data, iv, cipher_key