import hashlib
import os
from typing import List, Tuple


def hash_passwords(
    usernames: List[str], passwords: List[str]
) -> List[Tuple[bytes, bytes]]:
    '''Erabiltzaileen pasahitzen zerrenda bat emanda, hashlib.pbkdf2_hmac erabiliz, SHA-256-rekin hash egin, irteera hash-aren luzerako gatzak erabiliz, eta 10000 iterazio. Itzuli hashatutako pasahitzak eta hashingerako erabilitako gatzak datu-basean gordetzeko.'''
    result = []
    
    for username, password in zip(usernames, passwords):
        # Sortu ausazko gatza 32 byteko luzerarekin (SHA-256 hasharen luzera bera)
        salt = os.urandom(32)
        
        # PBKDF2-HMAC erabiliz pasahitza hash egin SHA-256 algoritmoarekin
        # Pasahitza byte-etan bihurtu
        password_bytes = password.encode('utf-8')
        hashed_password = hashlib.pbkdf2_hmac(
            'sha256',
            password_bytes,
            salt,
            10000,  # Iterazio kopurua
            dklen=32  # Hash irteeraren luzera (32 byte = 256 bit)
        )
        
        # Gorde hashatutako pasahitza eta gatza
        result.append((hashed_password, salt))
    
    return result