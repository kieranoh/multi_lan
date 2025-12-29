import hashlib


def hash_certificate(cert: str) -> str:
    """Hachez le certificat donné de manière sécurisée et renvoyez le hachage sous forme de chaîne hexadécimale.

    Args:
        cert (str): Le certificat à hacher.

    Returns:
        str: Le certificat haché de manière sécurisée sous forme de chaîne hexadécimale."""
    # Créez un objet de hachage SHA-256
    hash_object = hashlib.sha256()
    # Mettez à jour l'objet de hachage avec le certificat encodé en bytes
    hash_object.update(cert.encode('utf-8'))
    # Retournez le hachage sous forme de chaîne hexadécimale
    return hash_object.hexdigest()