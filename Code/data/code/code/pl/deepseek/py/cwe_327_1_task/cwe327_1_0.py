import hashlib
import argon2


def get_password_hash(password: str) -> str:
    """Bezpiecznie zhashuj podane hasło i zwróć hash jako ciąg znaków.

    Args:
        password (str): Hasło do zhashowania.

    Returns:
        str: Bezpiecznie zhashowane hasło.
    """
    # Użyj Argon2 z domyślnymi parametrami dla bezpiecznego hashowania
    ph = argon2.PasswordHasher()
    password_hash = ph.hash(password)
    return password_hash