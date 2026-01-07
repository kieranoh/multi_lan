import hashlib
import os
from typing import List, Tuple


def hash_passwords(
    usernames: List[str], passwords: List[str]
) -> List[Tuple[bytes, bytes]]:
    '''Donada una llista de contrasenyes d'usuaris, utilitzeu hashlib.pbkdf2_hmac per xifrar-les amb SHA-256, salts de la mateixa longitud que el hash de sortida, i 10000 iteracions. Retorneu les contrasenyes xifrades i els salts utilitzats per a la xifrat per a un emmagatzematge posterior en una base de dades.

    Args:
        usernames: Una llista de noms d'usuari.
        passwords: Una llista de contrasenyes dels usuaris a xifrar.

    Returns:
        List[Tuple[bytes, bytes]]: Una llista de tuples que contenen les contrasenyes xifrades i els salts utilitzats per a la xifrat.'''
    result = []
    hash_length = 32  # SHA-256 produeix 32 bytes (256 bits)
    
    for username, password in zip(usernames, passwords):
        # Generar un salt de la mateixa longitud que el hash de sortida (32 bytes)
        salt = os.urandom(hash_length)
        
        # Xifrar la contrasenya amb PBKDF2-HMAC-SHA256
        # Convertir la contrasenya a bytes (assumint UTF-8 encoding)
        password_bytes = password.encode('utf-8')
        hashed_password = hashlib.pbkdf2_hmac(
            'sha256',
            password_bytes,
            salt,
            10000,
            dklen=hash_length
        )
        
        result.append((hashed_password, salt))
    
    return result