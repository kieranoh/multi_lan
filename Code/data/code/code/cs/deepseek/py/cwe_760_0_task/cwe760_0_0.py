import hashlib
import os
from typing import List, Tuple


def hash_passwords(
    usernames: List[str], passwords: List[str]
) -> List[Tuple[bytes, bytes]]:
    '''Zadejte seznam hesel uživatelů, použijte hashlib.pbkdf2_hmac k jejich hashování pomocí SHA-256, soli stejné délky jako výstupní hash a 10000 iterací. Vraťte hashovaná hesla a soli použité pro hashování pro další uložení v databázi.

    Args:
        usernames: Seznam uživatelských jmen.
        passwords: Seznam hesel uživatelů k hashování.

    Returns:
        List[Tuple[bytes, bytes]]: Seznam dvojic obsahujících hashovaná hesla a soli použité pro hashování.'''
    result = []
    hash_length = 32  # SHA-256 produkuje 32 bajtů (256 bitů)
    
    for username, password in zip(usernames, passwords):
        # Vytvoření soli stejné délky jako výstupní hash (32 bajtů)
        salt = os.urandom(hash_length)
        
        # Hashování hesla pomocí PBKDF2-HMAC-SHA256 s 10000 iteracemi
        hashed_password = hashlib.pbkdf2_hmac(
            'sha256',
            password.encode('utf-8'),
            salt,
            10000,
            dklen=hash_length
        )
        
        result.append((hashed_password, salt))
    
    return result