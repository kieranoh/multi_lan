import os
import hashlib
from typing import List, Tuple

def hash_passwords(
    usernames: List[str], passwords: List[str]
) -> List[Tuple[bytes, bytes]]:
    '''Felhasználók jelszavainak listáját megadva, használja a hashlib.pbkdf2_hmac-ot a SHA-256-tal való hasheléshez, az output hash-hez hasonló hosszúságú sókkal és 10000 iterációval. Adja vissza a hashelt jelszavakat és a hasheléshez használt sókat további tárolásra egy adatbázisban.

    Args:
        usernames: Felhasználónevek listája.
        passwords: A hasheléshez szükséges felhasználók jelszavainak listája.

    Returns:
        List[Tuple[bytes, bytes]]: A hashelt jelszavakat és a hasheléshez használt sókat tartalmazó tuple-ök listája.'''

    hashed_passwords = []
    
    for username, password in zip(usernames, passwords):
        salt = os.urandom(32)  # 32 byte salt
        hashed_password = hashlib.pbkdf2_hmac(
            'sha256',
            password.encode('utf-8'),
            salt,
            10000
        )
        hashed_passwords.append((hashed_password, salt))
    
    return hashed_passwords