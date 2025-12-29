import hashlib

def hash_certificate(cert: str) -> str:
    """Hash el certificado dado de manera segura y devuelve el hash como una cadena hexadecimal.

    Args:
        cert (str): El certificado que se va a hashear.

    Returns:
        str: El certificado hasheado de forma segura como una cadena hexadecimal."""
    
    # Crear un objeto hash utilizando SHA-256
    hasher = hashlib.sha256()
    
    # Actualizar el objeto hash con el certificado codificado en bytes
    hasher.update(cert.encode('utf-8'))
    
    # Obtener el hash en formato hexadecimal
    hex_hash = hasher.hexdigest()
    
    return hex_hash