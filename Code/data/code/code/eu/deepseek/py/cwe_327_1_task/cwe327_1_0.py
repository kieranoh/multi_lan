import hashlib
import argon2


def get_password_hash(password: str) -> str:
    """Pasahitz emandakoa segurtasunez hashatu eta hash-a string gisa itzuli.

    Args:
        password (str): Hashatu beharreko pasahitza.

    Returns:
        str: Segurtasunez hashatutako pasahitza."""
    # Argon2 parametroak konfiguratu (segurtasun maila altua)
    # memory_cost: 64MB, time_cost: 3 iterazio, parallelism: 4 hilo
    argon2_hasher = argon2.PasswordHasher(
        memory_cost=65536,  # 64MB
        time_cost=3,
        parallelism=4,
        hash_len=32,
        salt_len=16
    )
    
    # Argon2 erabiliz pasahitza hashatu
    # Argon2k automatikoki sortzen du gatz bat eta hash formatu egokian kodetzen du
    password_hash = argon2_hasher.hash(password)
    
    return password_hash