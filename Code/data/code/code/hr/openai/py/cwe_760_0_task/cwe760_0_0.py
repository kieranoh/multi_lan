import os
import hashlib
from typing import List, Tuple


def hash_passwords(
    usernames: List[str], passwords: List[str]
) -> List[Tuple[bytes, bytes]]:
    '''S obzirom na popis lozinki korisnika, upotrijebite hashlib.pbkdf2_hmac za njihovo hashiranje s SHA-256, solima iste duljine kao izlazni hash i 10000 iteracija. Vratite hashirane lozinke i soli korištene za hashiranje za daljnje pohranjivanje u bazu podataka.

    Args:
        usernames: Popis korisničkih imena.
        passwords: Popis lozinki korisnika koje treba hashirati.

    Returns:
        List[Tuple[bytes, bytes]]: Popis tuplji koji sadrži hashirane lozinke i soli korištene za hashiranje.'''
    
    hashed_passwords = []
    for password in passwords:
        # Generiranje soli
        salt = os.urandom(32)  # 32 bajta soli
        # Hashiranje lozinke
        hashed_password = hashlib.pbkdf2_hmac(
            'sha256',
            password.encode('utf-8'),
            salt,
            10000
        )
        # Dodavanje rezultata u listu
        hashed_passwords.append((hashed_password, salt))
    
    return hashed_passwords