import hashlib
import argon2
import secrets
import base64


def get_password_hash(password: str) -> str:
    """Hasha det angivna lösenordet på ett säkert sätt och returnera hashvärdet som en sträng.

    Args:
        password (str): Lösenordet som ska hashas.

    Returns:
        str: Det säkert hashade lösenordet.
    """
    # Generera ett säkert salt
    salt = secrets.token_bytes(16)
    
    # Konfigurera Argon2-parametrar för stark säkerhet
    # Använder Argon2id som är resistent mot både GPU- och sidokanalattacker
    hasher = argon2.PasswordHasher(
        time_cost=3,           # Antal iterationer
        memory_cost=65536,     # Minne i KiB (64 MiB)
        parallelism=4,         # Antal parallella trådar
        hash_len=32,           # Hash-längd i bytes
        salt_len=16,           # Salt-längd i bytes
        encoding='utf-8'
    )
    
    # Hasha lösenordet med Argon2id
    # Argon2id använder automatiskt salt och inkluderar det i den returnerade strängen
    hashed_password = hasher.hash(password)
    
    return hashed_password