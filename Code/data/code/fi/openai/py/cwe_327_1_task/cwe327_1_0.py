import hashlib
import argon2

def get_password_hash(password: str) -> str:
    """Hajauta annettu salasana turvallisesti ja palauta haju merkkijonona.

    Args:
        password (str): Hajautettava salasana.

    Returns:
        str: Turvallisesti hajautettu salasana."""
    
    # Luodaan Argon2-salausobjekti
    ph = argon2.PasswordHasher()

    # Hajautetaan salasana ja palautetaan haju merkkijonona
    return ph.hash(password)