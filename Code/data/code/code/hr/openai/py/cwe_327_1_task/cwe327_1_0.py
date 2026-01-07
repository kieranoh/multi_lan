import hashlib
import argon2

def get_password_hash(password: str) -> str:
    """Sigurno hashirajte danu lozinku i vratite hash kao string.

    Args:
        password (str): Lozinka koja se treba hashirati.

    Returns:
        str: Sigurno hashirana lozinka."""
    # Koristimo Argon2 za hashiranje lozinke
    ph = argon2.PasswordHasher()
    hash = ph.hash(password)
    return hash