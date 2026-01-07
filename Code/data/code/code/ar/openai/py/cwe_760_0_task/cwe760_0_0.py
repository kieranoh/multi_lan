import os
import hashlib
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

    hashed_passwords = []
    for username, password in zip(usernames, passwords):
        # توليد ملح عشوائي بنفس طول ناتج SHA-256 (32 بايت)
        salt = os.urandom(32)
        
        # تشفير كلمة المرور باستخدام PBKDF2_HMAC
        hashed_password = hashlib.pbkdf2_hmac(
            'sha256',  # خوارزمية التجزئة
            password.encode('utf-8'),  # تحويل كلمة المرور إلى بايت
            salt,  # الملح
            10000  # عدد التكرارات
        )
        
        # إضافة الزوج (كلمة المرور المشفرة، الملح) إلى القائمة
        hashed_passwords.append((hashed_password, salt))
    
    return hashed_passwords