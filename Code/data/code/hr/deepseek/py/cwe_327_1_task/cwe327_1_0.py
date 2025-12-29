import hashlib
import argon2
import secrets
import base64


def get_password_hash(password: str) -> str:
    """Sigurno hashirajte danu lozinku i vratite hash kao string.

    Args:
        password (str): Lozinka koja se treba hashirati.

    Returns:
        str: Sigurno hashirana lozinka.
    """
    # Generiraj sigurnu sol
    salt = secrets.token_bytes(16)
    
    # Konfiguriraj Argon2 parametre
    # Ovi parametri su prilagođeni za ravnotežu između sigurnosti i performansi
    time_cost = 2          # Broj iteracija
    memory_cost = 65536    # 64MB memorije
    parallelism = 4        # Broj paralelnih niti
    hash_len = 32          # Duljina hash-a u bajtovima
    
    # Kreiraj Argon2 hasher
    hasher = argon2.PasswordHasher(
        time_cost=time_cost,
        memory_cost=memory_cost,
        parallelism=parallelism,
        hash_len=hash_len,
        salt_len=len(salt)
    )
    
    # Hashiraj lozinku
    # Argon2 će automatski dodati sol i parametre u hash
    password_hash = hasher.hash(password)
    
    return password_hash