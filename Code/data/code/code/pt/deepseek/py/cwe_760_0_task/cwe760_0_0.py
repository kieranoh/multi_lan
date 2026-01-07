import hashlib
import os
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
    # Verifica se as listas têm o mesmo comprimento
    if len(usernames) != len(passwords):
        raise ValueError("As listas de usernames e passwords devem ter o mesmo comprimento")
    
    # Tamanho do hash SHA-256 em bytes
    hash_size = 32  # 256 bits = 32 bytes
    results = []
    
    for username, password in zip(usernames, passwords):
        # Gera um salt aleatório do mesmo comprimento que o hash de saída
        salt = os.urandom(hash_size)
        
        # Converte a senha para bytes (assumindo codificação UTF-8)
        password_bytes = password.encode('utf-8')
        
        # Aplica o hash PBKDF2-HMAC com SHA-256
        hashed_password = hashlib.pbkdf2_hmac(
            'sha256',
            password_bytes,
            salt,
            10000,  # Número de iterações
            dklen=hash_size
        )
        
        # Adiciona a tupla (hashed_password, salt) à lista de resultados
        results.append((hashed_password, salt))
    
    return results