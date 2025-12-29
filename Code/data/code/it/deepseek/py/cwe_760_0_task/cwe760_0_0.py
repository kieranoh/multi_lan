import hashlib
import os
from typing import List, Tuple


def hash_passwords(
    usernames: List[str], passwords: List[str]
) -> List[Tuple[bytes, bytes]]:
    '''Data un elenco di password degli utenti, utilizza hashlib.pbkdf2_hmac per hashare con SHA-256, sali della stessa lunghezza dell'hash di output e 10000 iterazioni. Restituisci le password hashate e i sali utilizzati per l'hashing per ulteriore memorizzazione in un database.

    Args:
        usernames: Un elenco di nomi utente.
        passwords: Un elenco di password degli utenti da hashare.

    Returns:
        List[Tuple[bytes, bytes]]: Un elenco di tuple contenenti le password hashate e i sali utilizzati per l'hashing.'''
    
    # Verifica che le liste abbiano la stessa lunghezza
    if len(usernames) != len(passwords):
        raise ValueError("Le liste usernames e passwords devono avere la stessa lunghezza")
    
    result = []
    
    for username, password in zip(usernames, passwords):
        # Converti la password in bytes
        password_bytes = password.encode('utf-8')
        
        # Genera un sale casuale della stessa lunghezza dell'hash SHA-256 (32 byte)
        salt = os.urandom(32)
        
        # Esegui l'hashing con PBKDF2-HMAC-SHA256
        hashed_password = hashlib.pbkdf2_hmac(
            'sha256',
            password_bytes,
            salt,
            10000,
            dklen=32  # Lunghezza dell'hash di output (32 byte per SHA-256)
        )
        
        result.append((hashed_password, salt))
    
    return result