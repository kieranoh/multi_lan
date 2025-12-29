import os

def hash_passwords(
    usernames: List[str], passwords: List[str]
) -> List[Tuple[bytes, bytes]]:
    '''Erabiltzaileen pasahitzen zerrenda bat emanda, hashlib.pbkdf2_hmac erabiliz, SHA-256-rekin hash egin, irteera hash-aren luzerako gatzak erabiliz, eta 10000 iterazio. Itzuli hashatutako pasahitzak eta hashingerako erabilitako gatzak datu-basean gordetzeko.'''
    
    hashed_passwords = []
    
    for password in passwords:
        # Gatz aleatorioa sortu
        salt = os.urandom(16)
        # Pasahitza hashatu
        hashed_password = hashlib.pbkdf2_hmac(
            'sha256',
            password.encode('utf-8'),
            salt,
            10000
        )
        # Hashatutako pasahitza eta gatz aleatorioa gorde
        hashed_passwords.append((hashed_password, salt))
    
    return hashed_passwords