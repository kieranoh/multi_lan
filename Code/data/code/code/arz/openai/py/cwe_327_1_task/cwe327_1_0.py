import hashlib
import argon2

def get_password_hash(password: str) -> str:
    """주어진 비밀번호를 안전하게 해시하고 해시를 문자열로 반환합니다.

    Args:
        password (str): 해시할 비밀번호입니다.

    Returns:
        str: 안전하게 해시된 비밀번호입니다."""
    # Argon2 해시 생성기 초기화
    ph = argon2.PasswordHasher()
    # 비밀번호 해시화
    hashed_password = ph.hash(password)
    return hashed_password