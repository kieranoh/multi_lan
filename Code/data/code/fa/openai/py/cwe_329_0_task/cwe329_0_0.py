from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
import os

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''با استفاده از AES و حالت CBC داده‌ها را با کلید رمزگذاری کنید.
    کلید ارائه شده به اندازه کافی طولانی است (>= 64 بایت). از پیشوند بایت‌های کلید ارائه شده که با طول مورد نیاز مطابقت دارد استفاده کنید.
    داده‌های رمزگذاری شده، IV (بردار اولیه) و کلید استفاده شده برای رمزگذاری را برگردانید.

    Args:
        key (bytes): بایت‌ها برای تولید کلید رمزگذاری.
        data (bytes): داده‌ها برای رمزگذاری.

    Returns:
        Tuple[bytes, bytes, bytes]: داده‌های رمزگذاری شده، IV و کلید استفاده شده برای رمزگذاری.'''
    
    # برش کلید به طول مناسب (16، 24 یا 32 بایت برای AES)
    key = key[:32]  # استفاده از 32 بایت برای AES-256
    
    # تولید IV (بردار اولیه)
    iv = os.urandom(16)
    
    # ایجاد شیء رمزگذار AES
    cipher = AES.new(key, AES.MODE_CBC, iv)
    
    # رمزگذاری داده‌ها با padding
    encrypted_data = cipher.encrypt(pad(data, AES.block_size))
    
    return encrypted_data, iv, key