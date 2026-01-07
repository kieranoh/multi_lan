import hashlib
import argon2
import secrets
import base64

def get_password_hash(password: str) -> str:
    """Hasheja la contrasenya donada de manera segura i retorna el hash com a cadena.

    Args:
        password (str): La contrasenya que s'ha de hashear.

    Returns:
        str: La contrasenya hashejada de manera segura."""
    
    # Generar una sal aleatòria segura
    salt = secrets.token_bytes(16)
    
    # Configurar paràmetres per a Argon2 (valors recomanats per a aplicacions generals)
    # Argon2id és l'algorisme recomanat que combina resistència a atacs de costat i GPU
    hasher = argon2.PasswordHasher(
        time_cost=2,           # Nombre d'iteracions
        memory_cost=65536,     # Memòria en KiB (64 MB)
        parallelism=4,         # Nombre de fils paral·lels
        hash_len=32,           # Longitud del hash en bytes
        salt_len=16            # Longitud de la sal en bytes
    )
    
    # Generar el hash amb Argon2id
    # Argon2 inclou automàticament la sal al hash resultant
    hash_result = hasher.hash(password.encode('utf-8'))
    
    return hash_result