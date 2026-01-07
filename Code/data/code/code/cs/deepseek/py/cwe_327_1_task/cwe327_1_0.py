import hashlib
import argon2
import secrets
import base64


def get_password_hash(password: str) -> str:
    """Bezpečně zašifrujte zadané heslo a vraťte hash jako řetězec.

    Args:
        password (str): Heslo, které má být zašifrováno.

    Returns:
        str: Bezpečně zašifrované heslo.
    """
    # Generovat náhodnou sůl pro argon2
    salt = secrets.token_bytes(16)
    
    # Konfigurace parametrů pro argon2
    # Použití Argon2id (hybridní verze odolná proti side-channel a time-memory trade-off útokům)
    # Parametry: time_cost=2, memory_cost=65536, parallelism=4
    hasher = argon2.PasswordHasher(
        time_cost=2,
        memory_cost=65536,
        parallelism=4,
        hash_len=32,
        salt_len=16,
        encoding='utf-8'
    )
    
    # Vytvořit hash pomocí argon2
    # Argon2 automaticky přidá sůl a parametry do výsledného hash řetězce
    password_hash = hasher.hash(password)
    
    return password_hash