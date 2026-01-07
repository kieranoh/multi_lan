from typing import Tuple
from Crypto.Cipher import AES, DES
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
    
    # اختيار خوارزمية AES (يمكن تغييرها إلى DES إذا رغبت)
    # نختار AES لأنها أكثر أمانًا من DES
    algorithm = "AES"
    
    if algorithm == "AES":
        # AES-256 يتطلب مفتاح 32 بايت (256 بت)
        key_length = 32
        iv_length = 16  # حجم بلوك AES
        cipher_class = AES
    elif algorithm == "DES":
        # DES يتطلب مفتاح 8 بايت (64 بت، مع 56 بت فعالة)
        key_length = 8
        iv_length = 8  # حجم بلوك DES
        cipher_class = DES
    else:
        raise ValueError(f"الخوارزمية {algorithm} غير مدعومة")
    
    # استخراج البايتات الأولى من المفتاح المقدم للوصول إلى الطول المطلوب
    if len(key) < key_length:
        raise ValueError(f"المفتاح المقدم قصير جدًا. المطلوب: {key_length}، المتوفر: {len(key)}")
    
    encryption_key = key[:key_length]
    
    # توليد IV عشوائي
    iv = get_random_bytes(iv_length)
    
    # إنشاء كائن التشفير في وضع CBC
    cipher = cipher_class.new(encryption_key, cipher_class.MODE_CBC, iv)
    
    # تطبيق padding على البيانات ثم تشفيرها
    # حجم البلوك يعتمد على الخوارزمية
    block_size = iv_length
    padded_data = pad(data, block_size)
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, encryption_key