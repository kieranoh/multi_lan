import hashlib
import argon2
import secrets
import base64


def get_password_hash(password: str) -> str:
    """Sigurno hash-ujte dati password i vratite hash kao string.

    Args:
        password (str): Password koji treba hash-ovati.

    Returns:
        str: Sigurno hash-ovani password.
    """
    # Generišemo sigurnu sol
    salt = secrets.token_bytes(16)
    
    # Konfigurišemo Argon2 parametre
    # Ovi parametri su podešeni za moderan balans između bezbednosti i performansi
    time_cost = 2          # Broj iteracija
    memory_cost = 65536    # 64MB memorije
    parallelism = 4        # Broj paralelnih niti
    hash_len = 32          # Dužina hash-a u bajtovima
    
    # Kreiraj Argon2 hash
    argon2_hasher = argon2.PasswordHasher(
        time_cost=time_cost,
        memory_cost=memory_cost,
        parallelism=parallelism,
        hash_len=hash_len,
        salt_len=len(salt)
    )
    
    # Generišemo hash
    # Argon2 interno upravlja soli, ali mi eksplicitno prosleđujemo našu sol
    # za konzistentnost u formatu izlaza
    hash_result = argon2_hasher.hash(password.encode('utf-8'))
    
    return hash_result