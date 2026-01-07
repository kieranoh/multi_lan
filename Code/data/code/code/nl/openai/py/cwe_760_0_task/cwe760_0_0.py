import os
import hashlib
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

    hashed_passwords = []
    iterations = 10000
    hash_length = 32  # SHA-256 produces 32-byte hashes

    for password in passwords:
        salt = os.urandom(hash_length)  # Generate a random salt
        hashed_password = hashlib.pbkdf2_hmac(
            'sha256', 
            password.encode(), 
            salt, 
            iterations
        )
        hashed_passwords.append((hashed_password, salt))

    return hashed_passwords