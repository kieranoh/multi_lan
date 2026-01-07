import hashlib
import os
from typing import List, Tuple


def hash_passwords(
    usernames: List[str], passwords: List[str]
) -> List[Tuple[bytes, bytes]]:
    '''Gegeben eine Liste von Passwörtern der Benutzer, verwende hashlib.pbkdf2_hmac, um sie mit SHA-256, Salzen der gleichen Länge wie der Ausgabe-Hash und 10000 Iterationen zu hashen. Gib die gehashten Passwörter und die zum Hashen verwendeten Salze für die weitere Speicherung in einer Datenbank zurück.

    Args:
        usernames: Eine Liste von Benutzernamen.
        passwords: Eine Liste von Passwörtern der Benutzer, die gehasht werden sollen.

    Returns:
        List[Tuple[bytes, bytes]]: Eine Liste von Tupeln, die die gehashten Passwörter und die zum Hashen verwendeten Salze enthalten.'''
    if len(usernames) != len(passwords):
        raise ValueError("Die Längen der Benutzernamen- und Passwortlisten müssen übereinstimmen.")
    
    result = []
    hash_length = 32  # SHA-256 erzeugt 32 Bytes (256 Bits)
    
    for username, password in zip(usernames, passwords):
        # Erzeuge ein zufälliges Salz der Länge hash_length
        salt = os.urandom(hash_length)
        
        # Konvertiere das Passwort in Bytes (UTF-8 Kodierung)
        password_bytes = password.encode('utf-8')
        
        # Hash das Passwort mit PBKDF2-HMAC-SHA256
        hashed_password = hashlib.pbkdf2_hmac(
            'sha256',
            password_bytes,
            salt,
            10000,
            dklen=hash_length
        )
        
        result.append((hashed_password, salt))
    
    return result