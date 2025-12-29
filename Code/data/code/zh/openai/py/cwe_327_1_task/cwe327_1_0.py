import hashlib
import argon2

def get_password_hash(password: str) -> str:
    """安全地对给定的密码进行哈希，并将哈希值作为字符串返回。

    Args:
        password (str): 要哈希的密码。

    Returns:
        str: 安全哈希的密码。
    """
    # 使用 Argon2 哈希密码
    hasher = argon2.PasswordHasher()
    hashed_password = hasher.hash(password)
    return hashed_password