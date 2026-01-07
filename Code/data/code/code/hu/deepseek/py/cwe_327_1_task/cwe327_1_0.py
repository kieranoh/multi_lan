import hashlib
import argon2
import secrets
import base64


def get_password_hash(password: str) -> str:
    """A megadott jelszót biztonságosan hasheljük, és a hash-t karakterláncként adjuk vissza.

    Args:
        password (str): A hashelendő jelszó.

    Returns:
        str: A biztonságosan hashelt jelszó.
    """
    # Só generálása
    salt = secrets.token_bytes(16)
    
    # Argon2 paraméterek beállítása
    time_cost = 2          # Iterációk száma
    memory_cost = 65536    # Memória költség (64 MB)
    parallelism = 4        # Párhuzamos szálak száma
    hash_len = 32          # Hash hossza bájtokban
    
    # Argon2 hash készítése
    argon2_hasher = argon2.PasswordHasher(
        time_cost=time_cost,
        memory_cost=memory_cost,
        parallelism=parallelism,
        hash_len=hash_len,
        salt_len=len(salt)
    )
    
    # Hash készítése
    password_hash = argon2_hasher.hash(password.encode('utf-8'), salt=salt)
    
    # SHA-256 hash készítése a jelszóról a sóval kombinálva (extra biztonság)
    combined = password.encode('utf-8') + salt
    sha256_hash = hashlib.sha256(combined).digest()
    
    # Az eredmény összeállítása: argon2 hash + ":" + base64(salt + sha256_hash)
    combined_hash = salt + sha256_hash
    combined_hash_b64 = base64.urlsafe_b64encode(combined_hash).decode('utf-8')
    
    # Végső hash formátum: argon2_hash:combined_b64_hash
    final_hash = f"{password_hash}:{combined_hash_b64}"
    
    return final_hash