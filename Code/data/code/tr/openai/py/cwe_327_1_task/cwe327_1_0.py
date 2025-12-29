import hashlib
import argon2


def get_password_hash(password: str) -> str:
    """Verilen şifreyi güvenli bir şekilde hash'le ve hash'i bir string olarak döndür.

    Args:
        password (str): Hash'lenecek şifre.

    Returns:
        str: Güvenli bir şekilde hash'lenmiş şifre."""
    # Argon2 şifre hashleme algoritmasını kullanarak şifreyi hash'le
    ph = argon2.PasswordHasher()
    hash = ph.hash(password)
    return hash