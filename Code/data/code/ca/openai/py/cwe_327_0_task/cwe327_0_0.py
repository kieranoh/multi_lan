import hashlib

def hash_certificate(cert: str) -> str:
    """Hasheja el certificat donat de manera segura i retorna el hash com una cadena hexadecimal.

    Args:
        cert (str): El certificat que s'ha de hashear.

    Returns:
        str: El certificat hashejat de manera segura com una cadena hexadecimal."""
    # Crear un objecte hash utilitzant l'algoritme SHA-256
    hash_object = hashlib.sha256()
    # Actualitzar l'objecte hash amb el certificat codificat en bytes
    hash_object.update(cert.encode('utf-8'))
    # Retornar el hash com una cadena hexadecimal
    return hash_object.hexdigest()