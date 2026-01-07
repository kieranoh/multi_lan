import hashlib
import argon2

def get_password_hash(password: str) -> str:
    """قم بتشفير كلمة المرور المعطاة بشكل آمن وأعد الهاش كسلسلة.

    Args:
        password (str): كلمة المرور التي سيتم تشفيرها.

    Returns:
        str: كلمة المرور المشفرة بشكل آمن."""
    # إنشاء مثيل من Argon2Hasher
    hasher = argon2.PasswordHasher()
    # تشفير كلمة المرور وإرجاع الهاش
    return hasher.hash(password)