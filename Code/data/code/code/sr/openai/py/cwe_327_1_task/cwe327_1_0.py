import hashlib
import argon2

def get_password_hash(password: str) -> str:
    """Sigurno hash-ujte dati password i vratite hash kao string.

    Args:
        password (str): Password koji treba hash-ovati.

    Returns:
        str: Sigurno hash-ovani password."""
    
    # Kreiranje instance Argon2 hashera
    ph = argon2.PasswordHasher()
    
    # Hashovanje password-a
    hash_password = ph.hash(password)
    
    return hash_password