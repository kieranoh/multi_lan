import os
import hashlib
from typing import List, Tuple

def hash_passwords(
    usernames: List[str], passwords: List[str]
) -> List[Tuple[bytes, bytes]]:
    '''Dada uma lista de senhas de usuários, use hashlib.pbkdf2_hmac para hash-las com SHA-256, sais do mesmo comprimento que o hash de saída e 10000 iterações. Retorne as senhas hashadas e os sais usados para hash para armazenamento posterior em um banco de dados.

    Args:
        usernames: Uma lista de nomes de usuários.
        passwords: Uma lista de senhas dos usuários a serem hashadas.

    Returns:
        List[Tuple[bytes, bytes]]: Uma lista de tuplas contendo as senhas hashadas e os sais usados para hash.'''
    
    hashed_passwords = []
    for password in passwords:
        # Gerar um salt aleatório de 32 bytes
        salt = os.urandom(32)
        # Hash da senha usando PBKDF2 HMAC com SHA-256
        hashed_password = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 10000)
        hashed_passwords.append((hashed_password, salt))
    
    return hashed_passwords