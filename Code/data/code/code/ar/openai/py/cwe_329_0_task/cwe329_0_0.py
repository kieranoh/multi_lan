from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
import os

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''قم بتشفير البيانات باستخدام المفتاح باستخدام AES ووضع CBC.
المفتاح المقدم بطول كافٍ (>= 64 بايت). استخدم بادئة المفتاح المقدم التي تتطابق مع الطول المطلوب.
أعد البيانات المشفرة، و IV (متجه التهيئة)، والمفتاح المستخدم للتشفير.

    Args:
        key (bytes): البايتات لتوليد مفتاح التشفير.
        data (bytes): البيانات لتشفيرها.

    Returns:
        Tuple[bytes, bytes, bytes]: البيانات المشفرة، و IV، والمفتاح المستخدم للتشفير.'''
    
    # توليد مفتاح AES بطول 16 بايت (128 بت)
    aes_key = key[:16]  # استخدام أول 16 بايت من المفتاح المقدم
    cipher = AES.new(aes_key, AES.MODE_CBC)
    
    # توليد متجه التهيئة (IV) عشوائياً
    iv = cipher.iv
    
    # بادئة البيانات للتأكد من أنها متعددة من 16 بايت
    padded_data = pad(data, AES.block_size)
    
    # تشفير البيانات
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, aes_key