import hashlib
import os
from typing import List, Tuple


def hash_passwords(
    usernames: List[str], passwords: List[str]
) -> List[Tuple[bytes, bytes]]:
    '''Dada una lista de contraseñas de usuarios, utiliza hashlib.pbkdf2_hmac para hasharlas con SHA-256, sales de la misma longitud que el hash de salida y 10000 iteraciones. Devuelve las contraseñas hasheadas y las sales utilizadas para el hash para su posterior almacenamiento en una base de datos.

    Args:
        usernames: Una lista de nombres de usuario.
        passwords: Una lista de contraseñas de los usuarios a hashear.

    Returns:
        List[Tuple[bytes, bytes]]: Una lista de tuplas que contienen las contraseñas hasheadas y las sales utilizadas para el hash.'''
    # Verificar que las listas tengan la misma longitud
    if len(usernames) != len(passwords):
        raise ValueError("Las listas de usuarios y contraseñas deben tener la misma longitud")
    
    result = []
    # Tamaño del hash SHA-256 en bytes
    hash_size = 32  # SHA-256 produce 32 bytes (256 bits)
    
    for username, password in zip(usernames, passwords):
        # Generar una sal aleatoria de la misma longitud que el hash de salida
        salt = os.urandom(hash_size)
        
        # Convertir la contraseña a bytes (asumiendo que está en formato string)
        password_bytes = password.encode('utf-8')
        
        # Aplicar PBKDF2-HMAC con SHA-256, 10000 iteraciones
        hashed_password = hashlib.pbkdf2_hmac(
            'sha256',
            password_bytes,
            salt,
            10000,
            dklen=hash_size
        )
        
        result.append((hashed_password, salt))
    
    return result