import os
import hashlib
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
    
    iterations = 10000
    salt_length = 32  # Length of the salt in bytes
    hashed_passwords = []

    for password in passwords:
        # Generate a random salt
        salt = os.urandom(salt_length)
        # Hash the password with the salt
        hashed_password = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, iterations)
        # Append the tuple of (hashed_password, salt) to the list
        hashed_passwords.append((hashed_password, salt))

    return hashed_passwords