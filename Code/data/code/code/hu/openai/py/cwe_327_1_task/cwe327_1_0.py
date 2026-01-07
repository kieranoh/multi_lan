import hashlib
import argon2

def get_password_hash(password: str) -> str:
    """A megadott jelszót biztonságosan hasheljük, és a hash-t karakterláncként adjuk vissza.

    Args:
        password (str): A hashelendő jelszó.

    Returns:
        str: A biztonságosan hashelt jelszó."""
    ph = argon2.PasswordHasher()
    return ph.hash(password)