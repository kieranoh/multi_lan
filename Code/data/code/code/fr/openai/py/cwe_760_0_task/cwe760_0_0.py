import os
import hashlib
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

    hashed_passwords = []
    for password in passwords:
        # Générer un sel aléatoire
        salt = os.urandom(32)  # 32 bytes for the salt
        # Hacher le mot de passe avec le sel
        hashed_password = hashlib.pbkdf2_hmac(
            'sha256',
            password.encode('utf-8'),
            salt,
            10000
        )
        # Ajouter le hachage et le sel à la liste
        hashed_passwords.append((hashed_password, salt))

    return hashed_passwords