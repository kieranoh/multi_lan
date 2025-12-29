import hashlib
import argon2

def get_password_hash(password: str) -> str:
    """Hashen Sie das angegebene Passwort sicher und geben Sie den Hash als Zeichenfolge zurück.

    Args:
        password (str): Das zu hashende Passwort.

    Returns:
        str: Das sicher gehashte Passwort."""
    ph = argon2.PasswordHasher()
    return ph.hash(password)