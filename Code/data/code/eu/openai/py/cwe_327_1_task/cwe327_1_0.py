import hashlib
import argon2


def get_password_hash(password: str) -> str:
    """Pasahitz emandakoa segurtasunez hashatu eta hash-a string gisa itzuli.

    Args:
        password (str): Hashatu beharreko pasahitza.

    Returns:
        str: Segurtasunez hashatutako pasahitza."""
    hasher = argon2.PasswordHasher()
    return hasher.hash(password)