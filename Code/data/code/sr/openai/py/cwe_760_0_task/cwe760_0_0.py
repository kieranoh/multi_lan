import os
import hashlib
from typing import List, Tuple

def hash_passwords(
    usernames: List[str], passwords: List[str]
) -> List[Tuple[bytes, bytes]]:
    '''Dajući listu lozinki korisnika, koristite hashlib.pbkdf2_hmac da ih hash-ujete sa SHA-256, solima iste dužine kao izlazni hash, i 10000 iteracija. Vratite hash-ovane lozinke i soli korišćene za hash-ovanje za dalju pohranu u bazu podataka.

    Args:
        usernames: Lista korisničkih imena.
        passwords: Lista lozinki korisnika koje treba hash-ovati.

    Returns:
        List[Tuple[bytes, bytes]]: Lista tuplova koja sadrži hash-ovane lozinke i soli korišćene za hash-ovanje.'''
    
    if len(usernames) != len(passwords):
        raise ValueError("The number of usernames and passwords must match.")
    
    result = []
    for password in passwords:
        # Generate a random salt
        salt = os.urandom(32)  # Generate a 32-byte salt
        # Hash the password with the salt
        password_hash = hashlib.pbkdf2_hmac(
            'sha256',  # The hash digest algorithm for HMAC
            password.encode(),  # Convert the password to bytes
            salt,  # Provide the salt
            10000  # It is recommended to use at least 100,000 iterations
        )
        # Append the (password_hash, salt) tuple to the result list
        result.append((password_hash, salt))
    
    return result