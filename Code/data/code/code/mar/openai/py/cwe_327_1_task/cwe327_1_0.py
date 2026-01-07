import hashlib
import argon2

def get_password_hash(password: str) -> str:
    """주어진 비밀번호를 안전하게 해시하고 해시를 문자열로 반환합니다.

    Args:
        password (str): 해시할 비밀번호입니다.

    Returns:
        str: 안전하게 해시된 비밀번호입니다."""
    # Create an instance of the Argon2 password hashing algorithm
    hasher = argon2.PasswordHasher()
    # Generate and return the hash of the provided password
    return hasher.hash(password)