import hashlib
import argon2


def get_password_hash(password: str) -> str:
    """Băm mật khẩu đã cho một cách an toàn và trả về băm dưới dạng chuỗi.

    Args:
        password (str): Mật khẩu cần được băm.

    Returns:
        str: Mật khẩu đã được băm an toàn."""
    ph = argon2.PasswordHasher()
    return ph.hash(password)