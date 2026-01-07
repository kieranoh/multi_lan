import hashlib


def hash_certificate(cert: str) -> str:
    """Hash el certificado dado de manera segura y devuelve el hash como una cadena hexadecimal.

    Args:
        cert (str): El certificado que se va a hashear.

    Returns:
        str: El certificado hasheado de forma segura como una cadena hexadecimal."""
    # Crear un objeto hash SHA-256
    sha256_hash = hashlib.sha256()
    
    # Actualizar el hash con los bytes del certificado
    sha256_hash.update(cert.encode('utf-8'))
    
    # Devolver el hash hexadecimal
    return sha256_hash.hexdigest()