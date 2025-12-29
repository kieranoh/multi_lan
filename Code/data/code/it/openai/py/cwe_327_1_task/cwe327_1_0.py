import hashlib
import argon2

def get_password_hash(password: str) -> str:
    """Crea un hash della password fornita in modo sicuro e restituisci l'hash come stringa.

    Args:
        password (str): La password da hashare.

    Returns:
        str: La password hashata in modo sicuro."""
    
    # Utilizza Argon2 per generare un hash sicuro della password
    ph = argon2.PasswordHasher()
    hash = ph.hash(password)
    
    return hash