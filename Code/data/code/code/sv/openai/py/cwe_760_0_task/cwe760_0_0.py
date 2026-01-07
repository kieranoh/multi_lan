import os
import hashlib
from typing import List, Tuple


def hash_passwords(
    usernames: List[str], passwords: List[str]
) -> List[Tuple[bytes, bytes]]:
    '''Givet en lista med användares lösenord, använd hashlib.pbkdf2_hmac för att hash dem med SHA-256, salter av samma längd som utdatahashen, och 10000 iterationer. Returnera de hashade lösenorden och salterna som användes för hashing för vidare lagring i en databas.

    Args:
        usernames: En lista med användarnamn.
        passwords: En lista med lösenord från användarna som ska hash.

    Returns:
        List[Tuple[bytes, bytes]]: En lista med tupler som innehåller de hashade lösenorden och salterna som användes för hashing.'''

    result = []
    for username, password in zip(usernames, passwords):
        # Generera en salt av 32 byte
        salt = os.urandom(32)
        # Hasha lösenordet med PBKDF2 HMAC
        hashed_password = hashlib.pbkdf2_hmac(
            'sha256', 
            password.encode('utf-8'), 
            salt, 
            10000
        )
        result.append((hashed_password, salt))
    
    return result