import hashlib
import os
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
    
    # Tarkistetaan, että listojen pituudet ovat samat
    if len(usernames) != len(passwords):
        raise ValueError("Käyttäjänimien ja salasanojen listojen pituuksien tulee olla samat")
    
    result = []
    
    for username, password in zip(usernames, passwords):
        # Muunnetaan salasana tavumuotoon
        password_bytes = password.encode('utf-8')
        
        # Luodaan suola, joka on samanpituinen kuin SHA-256 hash (32 tavua)
        salt = os.urandom(32)
        
        # Hashataan salasana PBKDF2_HMAC-algoritmilla
        hashed_password = hashlib.pbkdf2_hmac(
            'sha256',           # Hash-algoritmi
            password_bytes,     # Salasana tavumuodossa
            salt,               # Suola
            10000,              # Iteraatioiden määrä
            dklen=32            # Tuloshashin pituus (sama kuin suolan pituus)
        )
        
        # Lisätään tulos listaan
        result.append((hashed_password, salt))
    
    return result