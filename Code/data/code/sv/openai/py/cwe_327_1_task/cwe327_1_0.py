import hashlib
import argon2

def get_password_hash(password: str) -> str:
    """Hasha det angivna lösenordet på ett säkert sätt och returnera hashvärdet som en sträng.

    Args:
        password (str): Lösenordet som ska hashas.

    Returns:
        str: Det säkert hashade lösenordet."""
    # Skapa en instans av Argon2 hasharen
    ph = argon2.PasswordHasher()
    # Hasha lösenordet
    hashed_password = ph.hash(password)
    return hashed_password