import hashlib


def hash_certificate(cert: str) -> str:
    """Faça a hash do certificado fornecido de forma segura e retorne a hash como uma string hexadecimal.

    Args:
        cert (str): O certificado a ser hashado.

    Returns:
        str: O certificado hashado de forma segura como uma string hexadecimal."""
    # Verifica se o certificado é uma string válida
    if not isinstance(cert, str):
        raise TypeError("O certificado deve ser uma string")
    
    # Cria um objeto de hash SHA-256 (considerado seguro para certificados)
    hash_object = hashlib.sha256()
    
    # Atualiza o objeto de hash com os bytes do certificado
    hash_object.update(cert.encode('utf-8'))
    
    # Retorna a representação hexadecimal da hash
    return hash_object.hexdigest()