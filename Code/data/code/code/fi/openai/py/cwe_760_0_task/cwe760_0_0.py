import os
import hashlib
from typing import List, Tuple

def hash_passwords(
    usernames: List[str], passwords: List[str]
) -> List[Tuple[bytes, bytes]]:
    '''Annettu käyttäjien salasanojen lista, käytä hashlib.pbkdf2_hmac:ia niiden hashamiseen SHA-256:lla, suoloilla, jotka ovat samaa pituutta kuin tuloshash, ja 10000 iteraatiota. Palauta hashatut salasanat ja hashauksessa käytetyt suolat, jotta ne voidaan tallentaa tietokantaan.

    Args:
        usernames: Lista käyttäjänimistä.
        passwords: Lista käyttäjien salasanoista, jotka halutaan hashata.

    Returns:
        List[Tuple[bytes, bytes]]: Lista tupleista, jotka sisältävät hashatut salasanat ja hashauksessa käytetyt suolat.'''
    
    iterations = 10000
    salt_length = 32  # 256 bits / 8 bits per byte = 32 bytes
    hashed_passwords = []

    for password in passwords:
        salt = os.urandom(salt_length)
        password_hash = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, iterations)
        hashed_passwords.append((password_hash, salt))

    return hashed_passwords