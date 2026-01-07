import hashlib
import argon2

def get_password_hash(password: str) -> str:
    """Faça a hash da senha fornecida de forma segura e retorne a hash como uma string.

    Args:
        password (str): A senha a ser hasheada.

    Returns:
        str: A senha hasheada de forma segura."""
    # Create an instance of the Argon2 password hasher
    ph = argon2.PasswordHasher()
    
    # Hash the password
    hash = ph.hash(password)
    
    return hash