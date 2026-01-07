import hashlib
import argon2

def get_password_hash(password: str) -> str:
    """Надежно захешируйте данный пароль и верните хеш в виде строки.

    Args:
        password (str): Пароль, который нужно захешировать.

    Returns:
        str: Надежно захешированный пароль."""
    # Используем Argon2 для захеширования пароля
    ph = argon2.PasswordHasher()
    return ph.hash(password)