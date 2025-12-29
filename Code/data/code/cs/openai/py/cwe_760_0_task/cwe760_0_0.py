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
    
    # Zkontrolujte, že seznamy mají stejnou délku
    if len(usernames) != len(passwords):
        raise ValueError("Seznamy uživatelských jmen a hesel musí mít stejnou délku.")
    
    hashed_passwords = []
    
    for password in passwords:
        # Vytvoření soli
        salt = os.urandom(32)  # 32 byte salt
        # Hashování hesla
        hashed_password = hashlib.pbkdf2_hmac(
            'sha256',
            password.encode('utf-8'),
            salt,
            10000
        )
        # Přidání hashovaného hesla a soli do výsledného seznamu
        hashed_passwords.append((hashed_password, salt))
    
    return hashed_passwords