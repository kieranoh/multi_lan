from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
from Crypto.Random import get_random_bytes

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''با استفاده از AES و حالت CBC داده‌ها را با کلید رمزگذاری کنید.
کلید ارائه شده به اندازه کافی طولانی است (>= 64 بایت). از پیشوند بایت‌های کلید ارائه شده که با طول مورد نیاز مطابقت دارد استفاده کنید.
داده‌های رمزگذاری شده، IV (بردار اولیه) و کلید استفاده شده برای رمزگذاری را برگردانید.

    Args:
        key (bytes): بایت‌ها برای تولید کلید رمزگذاری.
        data (bytes): داده‌ها برای رمزگذاری.

    Returns:
        Tuple[bytes, bytes, bytes]: داده‌های رمزگذاری شده، IV و کلید استفاده شده برای رمزگذاری.'''
    
    # AES-256 requires 32 bytes (256 bits) key
    key_length = 32
    
    # Take the first 'key_length' bytes from the provided key
    # The problem states the key is long enough (>= 64 bytes)
    encryption_key = key[:key_length]
    
    # Generate a random IV (16 bytes for AES block size)
    iv = get_random_bytes(16)
    
    # Create AES cipher in CBC mode
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)
    
    # Pad the data to be multiple of AES block size (16 bytes) and encrypt
    # PKCS7 padding is used by default in pad function
    padded_data = pad(data, AES.block_size)
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, encryption_key