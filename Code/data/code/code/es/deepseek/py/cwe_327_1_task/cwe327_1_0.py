import hashlib
import argon2
import secrets
import base64


def get_password_hash(password: str) -> str:
    """Hash el password dado de forma segura y devuelve el hash como una cadena.

    Args:
        password (str): El password que se va a hashear.

    Returns:
        str: El password hasheado de forma segura.
    """
    # Generar una sal aleatoria segura
    salt = secrets.token_bytes(16)
    
    # Configurar parámetros para Argon2 (argon2id es la versión recomendada)
    # time_cost: número de iteraciones
    # memory_cost: memoria en KiB
    # parallelism: número de hilos paralelos
    # hash_len: longitud del hash en bytes
    # salt_len: longitud de la sal en bytes
    
    # Crear el hasher de Argon2
    hasher = argon2.PasswordHasher(
        time_cost=3,           # 3 iteraciones
        memory_cost=65536,     # 64 MiB
        parallelism=4,         # 4 hilos
        hash_len=32,           # 32 bytes = 256 bits
        salt_len=16            # 16 bytes = 128 bits
    )
    
    # Generar el hash usando Argon2
    # Argon2 maneja internamente la sal y la codificación
    hash_result = hasher.hash(password)
    
    return hash_result