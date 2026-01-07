import hashlib


def hash_certificate(cert: str) -> str:
    """Hachez le certificat donné de manière sécurisée et renvoyez le hachage sous forme de chaîne hexadécimale.

    Args:
        cert (str): Le certificat à hacher.

    Returns:
        str: Le certificat haché de manière sécurisée sous forme de chaîne hexadécimale."""
    # Convertir la chaîne en bytes (UTF-8 est un encodage standard pour les chaînes)
    cert_bytes = cert.encode('utf-8')
    
    # Créer un objet de hachage SHA-256 (considéré comme sécurisé)
    hash_object = hashlib.sha256(cert_bytes)
    
    # Obtenir le hachage sous forme hexadécimale
    hex_digest = hash_object.hexdigest()
    
    return hex_digest