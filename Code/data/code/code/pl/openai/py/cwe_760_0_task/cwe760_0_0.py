import hashlib
import os
from typing import List, Tuple

def hash_passwords(
    usernames: List[str], passwords: List[str]
) -> List[Tuple[bytes, bytes]]:
    '''Mając listę haseł użytkowników, użyj hashlib.pbkdf2_hmac, aby je zhashować za pomocą SHA-256, sól o tej samej długości co wynikowy hash oraz 10000 iteracji. Zwróć zhashowane hasła i sole użyte do haszowania do dalszego przechowywania w bazie danych.

    Args:
        usernames: Lista nazw użytkowników.
        passwords: Lista haseł użytkowników do zhashowania.

    Returns:
        List[Tuple[bytes, bytes]]: Lista krotek zawierających zhashowane hasła i sole użyte do haszowania.'''
    
    hashed_passwords = []
    for password in passwords:
        # Generacja soli
        salt = os.urandom(32)  # 32 bytes for salt
        # Haszowanie hasła
        hashed_password = hashlib.pbkdf2_hmac(
            'sha256',
            password.encode(),
            salt,
            10000
        )
        hashed_passwords.append((hashed_password, salt))
    
    return hashed_passwords