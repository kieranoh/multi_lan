import hashlib
import os
from typing import List, Tuple


def hash_passwords(
    usernames: List[str], passwords: List[str]
) -> List[Tuple[bytes, bytes]]:
    '''Étant donné une liste de mots de passe d'utilisateurs, utilisez hashlib.pbkdf2_hmac pour les hacher avec SHA-256, des sels de la même longueur que le hachage de sortie, et 10000 itérations. Retournez les mots de passe hachés et les sels utilisés pour le hachage pour un stockage ultérieur dans une base de données.

    Args:
        usernames: Une liste de noms d'utilisateur.
        passwords: Une liste de mots de passe des utilisateurs à hacher.

    Returns:
        List[Tuple[bytes, bytes]]: Une liste de tuples contenant les mots de passe hachés et les sels utilisés pour le hachage.'''
    # Vérification des entrées
    if len(usernames) != len(passwords):
        raise ValueError("Les listes usernames et passwords doivent avoir la même longueur")
    
    result = []
    hash_length = 32  # Longueur du hachage SHA-256 en bytes
    
    for username, password in zip(usernames, passwords):
        # Générer un sel aléatoire de la même longueur que le hachage de sortie
        salt = os.urandom(hash_length)
        
        # Convertir le mot de passe en bytes (encodage UTF-8)
        password_bytes = password.encode('utf-8')
        
        # Hacher le mot de passe avec PBKDF2-HMAC-SHA256
        hashed_password = hashlib.pbkdf2_hmac(
            'sha256',
            password_bytes,
            salt,
            10000,
            dklen=hash_length
        )
        
        # Ajouter le tuple (hashed_password, salt) à la liste des résultats
        result.append((hashed_password, salt))
    
    return result