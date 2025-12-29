import hashlib
import os
from typing import List, Tuple


def hash_passwords(
    usernames: List[str], passwords: List[str]
) -> List[Tuple[bytes, bytes]]:
    '''بالنظر إلى قائمة من كلمات مرور المستخدمين، استخدم hashlib.pbkdf2_hmac لتشفيرها باستخدام SHA-256، وأملاح بنفس طول ناتج التشفير، و10000 تكرار. أعد كلمات المرور المشفرة والأملاح المستخدمة للتشفير للتخزين الإضافي في قاعدة بيانات.

    Args:
        usernames: قائمة بأسماء المستخدمين.
        passwords: قائمة بكلمات مرور المستخدمين للتشفير.

    Returns:
        List[Tuple[bytes, bytes]]: قائمة من الأزواج تحتوي على كلمات المرور المشفرة والأملاح المستخدمة للتشفير.'''
    
    # التحقق من أن أطوال القويتين متطابقة
    if len(usernames) != len(passwords):
        raise ValueError("يجب أن يكون طول قائمة أسماء المستخدمين مساوياً لطول قائمة كلمات المرور")
    
    result = []
    hash_length = 32  # طول ناتج SHA-256 بالبايت
    
    for username, password in zip(usernames, passwords):
        # إنشاء ملح عشوائي بنفس طول ناتج التشفير
        salt = os.urandom(hash_length)
        
        # تحويل كلمة المرور إلى بايتات
        password_bytes = password.encode('utf-8')
        
        # تشفير كلمة المرور باستخدام PBKDF2-HMAC-SHA-256
        hashed_password = hashlib.pbkdf2_hmac(
            'sha256',
            password_bytes,
            salt,
            10000,  # عدد التكرارات
            dklen=hash_length
        )
        
        result.append((hashed_password, salt))
    
    return result