import hashlib
import os
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
    
    # Kontrollera att listorna har samma längd
    if len(usernames) != len(passwords):
        raise ValueError("usernames och passwords måste ha samma längd")
    
    result = []
    
    for username, password in zip(usernames, passwords):
        # Konvertera lösenordet till bytes
        password_bytes = password.encode('utf-8')
        
        # Generera ett salt med samma längd som SHA-256 hash (32 bytes)
        salt = os.urandom(32)
        
        # Hasha lösenordet med PBKDF2-HMAC-SHA256
        hashed_password = hashlib.pbkdf2_hmac(
            'sha256',
            password_bytes,
            salt,
            10000
        )
        
        result.append((hashed_password, salt))
    
    return result