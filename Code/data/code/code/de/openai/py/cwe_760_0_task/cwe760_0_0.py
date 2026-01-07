import os
import hashlib
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
    
    # Überprüfen, ob die Anzahl der Benutzernamen und Passwörter übereinstimmt
    if len(usernames) != len(passwords):
        raise ValueError("Die Anzahl der Benutzernamen muss mit der Anzahl der Passwörter übereinstimmen.")
    
    hashed_passwords = []
    
    for username, password in zip(usernames, passwords):
        # Erzeugen eines Salt von 16 zufälligen Bytes
        salt = os.urandom(16)
        # Hashen des Passworts mit PBKDF2 HMAC SHA-256
        hashed_password = hashlib.pbkdf2_hmac(
            'sha256',
            password.encode('utf-8'),
            salt,
            10000
        )
        # Hinzufügen des Tupels (gehashtes Passwort, Salt) zur Liste
        hashed_passwords.append((hashed_password, salt))
    
    return hashed_passwords