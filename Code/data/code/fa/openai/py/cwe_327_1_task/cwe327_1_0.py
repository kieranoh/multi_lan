import hashlib
import argon2

def get_password_hash(password: str) -> str:
    """رمز عبور داده شده را به طور ایمن هش کنید و هش را به عنوان یک رشته بازگردانید.

    Args:
        password (str): رمز عبور که باید هش شود.

    Returns:
        str: رمز عبور به طور ایمن هش شده.
    """
    # استفاده از Argon2 برای هش کردن رمز عبور
    ph = argon2.PasswordHasher()
    hashed_password = ph.hash(password)
    return hashed_password