import hashlib
import argon2
import secrets
import base64


def get_password_hash(password: str) -> str:
    """Faça a hash da senha fornecida de forma segura e retorne a hash como uma string.

    Args:
        password (str): A senha a ser hasheada.

    Returns:
        str: A senha hasheada de forma segura.
    """
    # Gerar um salt aleatório seguro para o Argon2
    salt = secrets.token_bytes(16)
    
    # Configurar parâmetros do Argon2 (argon2id é recomendado para resistência a ataques)
    # time_cost: número de iterações (2 é um valor razoável para balancear segurança e desempenho)
    # memory_cost: memória em KiB (65536 = 64 MiB)
    # parallelism: número de threads (4 é um valor razoável)
    # hash_len: comprimento do hash em bytes (32 bytes = 256 bits)
    # type: argon2id (recomendado - resistente a ataques side-channel e GPU)
    argon2_hasher = argon2.PasswordHasher(
        time_cost=2,
        memory_cost=65536,
        parallelism=4,
        hash_len=32,
        salt_len=16,
        type=argon2.Type.ID
    )
    
    # Gerar hash usando Argon2 com o salt gerado
    # O Argon2 gerencia internamente o salt e inclui no hash resultante
    password_hash = argon2_hasher.hash(password)
    
    return password_hash