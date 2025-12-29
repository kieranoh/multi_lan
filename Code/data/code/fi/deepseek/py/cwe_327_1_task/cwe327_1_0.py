import hashlib
import argon2
import secrets
import base64


def get_password_hash(password: str) -> str:
    """Hajauta annettu salasana turvallisesti ja palauta haju merkkijonona.

    Args:
        password (str): Hajautettava salasana.

    Returns:
        str: Turvallisesti hajautettu salasana.
    """
    # Luodaan suola (salt) turvallisesti
    salt = secrets.token_bytes(16)
    
    # Määritellään Argon2-parametrit
    # time_cost: iterointien määrä (suurempi = turvallisempi mutta hitaampi)
    # memory_cost: käytetty muisti kilotavuina
    # parallelism: rinnakkaisten säikeiden määrä
    # hash_len: tulosteen pituus tavuina
    time_cost = 2
    memory_cost = 65536  # 64 MB
    parallelism = 4
    hash_len = 32
    
    # Luodaan Argon2-hasher
    hasher = argon2.PasswordHasher(
        time_cost=time_cost,
        memory_cost=memory_cost,
        parallelism=parallelism,
        hash_len=hash_len,
        salt_len=len(salt)
    )
    
    # Hashataan salasana Argon2:lla
    # Argon2 sisältää suolan ja parametrit hash-tulosteeseen
    password_hash = hasher.hash(password)
    
    return password_hash