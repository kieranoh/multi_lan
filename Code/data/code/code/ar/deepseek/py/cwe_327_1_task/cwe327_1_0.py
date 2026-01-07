import hashlib
import argon2
import secrets
import base64


def get_password_hash(password: str) -> str:
    """قم بتشفير كلمة المرور المعطاة بشكل آمن وأعد الهاش كسلسلة.

    Args:
        password (str): كلمة المرور التي سيتم تشفيرها.

    Returns:
        str: كلمة المرور المشفرة بشكل آمن."""
    
    # توليد ملح عشوائي آمن
    salt = secrets.token_bytes(16)
    
    # تكوين معلمات Argon2
    # استخدام Argon2id (المزيج الموصى به من مقاومة هجمات GPU والتوقيت الثابت)
    # معلمات متوسطة الأمان (يمكن تعديلها حسب احتياجات الأمان)
    hasher = argon2.PasswordHasher(
        time_cost=2,          # عدد التكرارات
        memory_cost=65536,    # استخدام الذاكرة بالكيلوبايت
        parallelism=4,        # عدد الخيوط
        hash_len=32,          # طول الهاش بالبايت
        salt_len=16,          # طول الملح بالبايت
        encoding='utf-8'      # الترميز
    )
    
    # إنشاء الهاش باستخدام Argon2id
    # سيقوم argon2 بإضافة الملح تلقائياً وتضمين المعلمات في السلسلة الناتجة
    password_hash = hasher.hash(password)
    
    return password_hash