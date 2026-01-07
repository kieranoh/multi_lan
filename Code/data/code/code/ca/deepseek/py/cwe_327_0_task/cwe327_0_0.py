import hashlib


def hash_certificate(cert: str) -> str:
    """Hasheja el certificat donat de manera segura i retorna el hash com una cadena hexadecimal.

    Args:
        cert (str): El certificat que s'ha de hashear.

    Returns:
        str: El certificat hashejat de manera segura com una cadena hexadecimal."""
    # Convertir la cadena del certificat a bytes
    cert_bytes = cert.encode('utf-8')
    
    # Crear un objecte hash SHA-256 (un algorisme de hash criptogràfic segur)
    hash_object = hashlib.sha256(cert_bytes)
    
    # Obtenir el hash en format hexadecimal
    hex_digest = hash_object.hexdigest()
    
    return hex_digest