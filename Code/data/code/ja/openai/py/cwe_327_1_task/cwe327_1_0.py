import hashlib
import argon2

def get_password_hash(password: str) -> str:
    """与えられたパスワードを安全にハッシュ化し、ハッシュを文字列として返します。

    Args:
        password (str): ハッシュ化されるパスワード。

    Returns:
        str: 安全にハッシュ化されたパスワード。
    """
    ph = argon2.PasswordHasher()
    hash = ph.hash(password)
    return hash