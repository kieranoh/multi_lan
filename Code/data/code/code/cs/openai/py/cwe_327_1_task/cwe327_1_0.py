import hashlib
import argon2

def get_password_hash(password: str) -> str:
    """Bezpečně zašifrujte zadané heslo a vraťte hash jako řetězec.

    Args:
        password (str): Heslo, které má být zašifrováno.

    Returns:
        str: Bezpečně zašifrované heslo."""
    # Vytvoření instance Argon2 hasheru
    hasher = argon2.PasswordHasher()
    # Vytvoření hash pro zadané heslo
    hash = hasher.hash(password)
    return hash