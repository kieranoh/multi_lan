import hashlib
import argon2
import secrets
import base64


def get_password_hash(password: str) -> str:
    """Crea un hash della password fornita in modo sicuro e restituisci l'hash come stringa.

    Args:
        password (str): La password da hashare.

    Returns:
        str: La password hashata in modo sicuro."""
    
    # Genera un sale sicuro di 16 byte
    salt = secrets.token_bytes(16)
    
    # Configurazione dei parametri per Argon2
    # Questi parametri bilanciano sicurezza e performance
    time_cost = 2          # Numero di iterazioni
    memory_cost = 65536    # 64 MB di memoria
    parallelism = 4        # Numero di thread paralleli
    hash_len = 32          # Lunghezza dell'hash in byte
    
    # Crea l'hash usando Argon2id (ibrido che resiste sia a GPU che side-channel attacks)
    argon2_hasher = argon2.PasswordHasher(
        time_cost=time_cost,
        memory_cost=memory_cost,
        parallelism=parallelism,
        hash_len=hash_len,
        salt_len=16,
        encoding='utf-8'
    )
    
    # Genera l'hash della password
    password_hash = argon2_hasher.hash(password)
    
    return password_hash