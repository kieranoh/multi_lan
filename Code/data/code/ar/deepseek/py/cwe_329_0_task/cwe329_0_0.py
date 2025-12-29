from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
from Crypto.Random import get_random_bytes

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''قم بتشفير البيانات باستخدام المفتاح باستخدام AES ووضع CBC.
المفتاح المقدم بطول كافٍ (>= 64 بايت). استخدم بادئة المفتاح المقدم التي تتطابق مع الطول المطلوب.
أعد البيانات المشفرة، و IV (متجه التهيئة)، والمفتاح المستخدم للتشفير.

    Args:
        key (bytes): البايتات لتوليد مفتاح التشفير.
        data (bytes): البيانات لتشفيرها.

    Returns:
        Tuple[bytes, bytes, bytes]: البيانات المشفرة، و IV، والمفتاح المستخدم للتشفير.'''
    
    # التحقق من أن طول المفتاح كافٍ (64 بايت على الأقل)
    if len(key) < 64:
        raise ValueError("يجب أن يكون طول المفتاح 64 بايت على الأقل")
    
    # استخدام أول 32 بايت من المفتاح كمفتاح AES-256
    # AES-256 يتطلب مفتاحًا بطول 32 بايت (256 بت)
    aes_key = key[:32]
    
    # توليد IV عشوائي بطول 16 بايت (طول كتلة AES)
    iv = get_random_bytes(16)
    
    # إنشاء كائن التشفير AES في وضع CBC
    cipher = AES.new(aes_key, AES.MODE_CBC, iv)
    
    # تطبيق padding على البيانات ثم تشفيرها
    # طول الكتلة لـ AES هو 16 بايت
    padded_data = pad(data, AES.block_size)
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, aes_key