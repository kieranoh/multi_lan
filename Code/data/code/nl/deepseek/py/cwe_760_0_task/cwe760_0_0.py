import hashlib
import os
from typing import List, Tuple


def hash_passwords(
    usernames: List[str], passwords: List[str]
) -> List[Tuple[bytes, bytes]]:
    '''Gegeven een lijst van wachtwoorden van gebruikers, gebruik hashlib.pbkdf2_hmac om ze te hashen met SHA-256, zouten van dezelfde lengte als de uitvoerhash, en 10000 iteraties. Geef de gehashte wachtwoorden en de zouten die zijn gebruikt voor het hashen terug voor verdere opslag in een database.

    Args:
        usernames: Een lijst van gebruikersnamen.
        passwords: Een lijst van wachtwoorden van de gebruikers om te hashen.

    Returns:
        List[Tuple[bytes, bytes]]: Een lijst van tuples met de gehashte wachtwoorden en de zouten die zijn gebruikt voor het hashen.'''
    result = []
    # SHA-256 produceert een 32-byte hash
    hash_length = 32
    
    for username, password in zip(usernames, passwords):
        # Genereer een willekeurig zout van dezelfde lengte als de hash (32 bytes)
        salt = os.urandom(hash_length)
        
        # Converteer het wachtwoord naar bytes (gebruik UTF-8 encoding)
        password_bytes = password.encode('utf-8')
        
        # Hash het wachtwoord met PBKDF2-HMAC-SHA256
        hashed_password = hashlib.pbkdf2_hmac(
            'sha256',
            password_bytes,
            salt,
            10000,
            dklen=hash_length
        )
        
        result.append((hashed_password, salt))
    
    return result