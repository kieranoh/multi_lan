from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''قم بتشفير البيانات باستخدام المفتاح باستخدام وضع CBC.
المفتاح المقدم طويل بما يكفي (>= 64 بايت) لجميع الخوارزميات المتاحة. اختر خوارزمية واحدة فقط للتنفيذ واستخدم بادئة بايت المفتاح المقدم التي تتطابق مع الطول المطلوب. لا تختار الخوارزمية بناءً على طول المفتاح.
أعد البيانات المشفرة، و IV (متجه التهيئة)، والمفتاح المستخدم للتشفير.

    Args:
        key (bytes): البايتات لتوليد مفتاح التشفير.
        data (bytes): البيانات لتشفيرها.

    Returns:
        Tuple[bytes, bytes, bytes]: البيانات المشفرة، و IV، والمفتاح المستخدم للتشفير.'''

    # اختر الطول المناسب للمفتاح (16 بايت لتشفير AES-128)
    aes_key = key[:16]  # تأخذ أول 16 بايت من المفتاح
    cipher = AES.new(aes_key, AES.MODE_CBC)  # تهيئة التشفير في وضع CBC
    iv = cipher.iv  # الحصول على متجه التهيئة
    padded_data = pad(data, AES.block_size)  # إضافة حشو للبيانات
    encrypted_data = cipher.encrypt(padded_data)  # تشفير البيانات

    return encrypted_data, iv, aes_key  # إرجاع البيانات المشفرة، IV، والمفتاح المستخدم