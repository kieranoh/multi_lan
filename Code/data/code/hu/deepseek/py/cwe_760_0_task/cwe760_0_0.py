import hashlib
import os
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
    result = []
    # SHA-256 hash output hossza 32 bájt, ezért a só hossza is 32 bájt lesz
    salt_length = 32
    
    for username, password in zip(usernames, passwords):
        # Generáljunk egy véletlen sót a megadott hosszal
        salt = os.urandom(salt_length)
        # Hasheljük a jelszót PBKDF2-HMAC-SHA256 használatával
        hashed_password = hashlib.pbkdf2_hmac(
            'sha256',
            password.encode('utf-8'),
            salt,
            10000
        )
        result.append((hashed_password, salt))
    
    return result