import hashlib
import argon2

def get_password_hash(password: str) -> str:
    """Hachez le mot de passe donné de manière sécurisée et renvoyez le hachage sous forme de chaîne.

    Args:
        password (str): Le mot de passe à hacher.

    Returns:
        str: Le mot de passe haché de manière sécurisée."""
    ph = argon2.PasswordHasher()
    return ph.hash(password)