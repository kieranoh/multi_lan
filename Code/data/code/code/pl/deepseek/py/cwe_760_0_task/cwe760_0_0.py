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
    result = []
    
    # Długość hasha SHA-256 w bajtach
    hash_length = 32  # 256 bitów / 8 = 32 bajty
    
    for username, password in zip(usernames, passwords):
        # Generuj sól o długości równej długości hasha
        salt = os.urandom(hash_length)
        
        # Konwertuj hasło na bajty
        password_bytes = password.encode('utf-8')
        
        # Hashuj hasło używając PBKDF2-HMAC-SHA256
        hashed_password = hashlib.pbkdf2_hmac(
            'sha256',
            password_bytes,
            salt,
            10000,
            dklen=hash_length
        )
        
        result.append((hashed_password, salt))
    
    return result