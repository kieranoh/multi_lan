import hashlib
import argon2

def get_password_hash(password: str) -> str:
    """Hash el password dado de forma segura y devuelve el hash como una cadena.

    Args:
        password (str): El password que se va a hashear.

    Returns:
        str: El password hasheado de forma segura."""
    ph = argon2.PasswordHasher()
    return ph.hash(password)