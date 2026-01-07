import hashlib
import os
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
    
    # Provera da li su liste iste dužine
    if len(usernames) != len(passwords):
        raise ValueError("Liste usernames i passwords moraju biti iste dužine")
    
    result = []
    
    for username, password in zip(usernames, passwords):
        # Generisanje soli iste dužine kao SHA-256 hash (32 bajta)
        salt = os.urandom(32)
        
        # Hash-ovanje lozinke sa PBKDF2-HMAC-SHA256
        # Konvertujemo lozinku u bajtove
        password_bytes = password.encode('utf-8')
        
        # Hash-ujemo sa 10000 iteracija
        hashed_password = hashlib.pbkdf2_hmac(
            'sha256',
            password_bytes,
            salt,
            10000
        )
        
        result.append((hashed_password, salt))
    
    return result