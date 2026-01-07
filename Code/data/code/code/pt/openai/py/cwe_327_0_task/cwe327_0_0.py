import hashlib

def hash_certificate(cert: str) -> str:
    """Faça a hash do certificado fornecido de forma segura e retorne a hash como uma string hexadecimal.

    Args:
        cert (str): O certificado a ser hashado.

    Returns:
        str: O certificado hashado de forma segura como uma string hexadecimal."""
    
    # Cria um objeto hash usando SHA-256
    sha256_hash = hashlib.sha256()
    
    # Atualiza o objeto hash com os dados do certificado
    sha256_hash.update(cert.encode('utf-8'))
    
    # Retorna a hash como uma string hexadecimal
    return sha256_hash.hexdigest()