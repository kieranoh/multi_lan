import hashlib
import os
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
    result = []
    # SHA-256 proizvodi 32-byte (256-bit) hash
    hash_length = 32
    
    for username, password in zip(usernames, passwords):
        # Generiraj sol iste duljine kao izlazni hash (32 bajta)
        salt = os.urandom(hash_length)
        
        # Hashiraj lozinku koristeći PBKDF2-HMAC-SHA256 s 10000 iteracija
        # Pretvori lozinku u bytes koristeći UTF-8 kodiranje
        password_bytes = password.encode('utf-8')
        hashed_password = hashlib.pbkdf2_hmac(
            'sha256',
            password_bytes,
            salt,
            10000,
            dklen=hash_length
        )
        
        result.append((hashed_password, salt))
    
    return result