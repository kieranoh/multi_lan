import os
import hashlib
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
    
    hashed_passwords = []
    for password in passwords:
        # Generar un salt aleatori
        salt = os.urandom(32)
        # Xifrar la contrasenya
        hashed_password = hashlib.pbkdf2_hmac(
            'sha256',
            password.encode('utf-8'),
            salt,
            10000
        )
        # Afegir a la llista el tuple de (contrassenya xifrada, salt)
        hashed_passwords.append((hashed_password, salt))
    
    return hashed_passwords