import os
import hashlib
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

    hashed_passwords = []
    for password in passwords:
        # Generar una sal aleatoria de 32 bytes
        salt = os.urandom(32)
        # Hashear la contraseña con PBKDF2 HMAC utilizando SHA-256
        hashed_password = hashlib.pbkdf2_hmac(
            'sha256', 
            password.encode('utf-8'), 
            salt, 
            10000
        )
        # Agregar la tupla (hash, salt) a la lista
        hashed_passwords.append((hashed_password, salt))
    
    return hashed_passwords