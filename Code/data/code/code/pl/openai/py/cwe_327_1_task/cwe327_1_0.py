import hashlib
import argon2

def get_password_hash(password: str) -> str:
    """Bezpiecznie zhashuj podane hasło i zwróć hash jako ciąg znaków.

    Args:
        password (str): Hasło do zhashowania.

    Returns:
        str: Bezpiecznie zhashowane hasło."""
    hasher = argon2.PasswordHasher()
    return hasher.hash(password)