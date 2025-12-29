import hashlib


def hash_certificate(cert: str) -> str:
    """Hash het gegeven certificaat veilig en retourneer de hash als een hexadecimale string.

    Args:
        cert (str): Het certificaat dat gehasht moet worden.

    Returns:
        str: Het veilig gehashte certificaat als een hexadecimale string.
    """
    # Converteer de certificaatstring naar bytes
    cert_bytes = cert.encode('utf-8')
    
    # Maak een SHA-256 hash object
    hash_object = hashlib.sha256()
    
    # Update het hash object met de certificaatbytes
    hash_object.update(cert_bytes)
    
    # Retourneer de hexadecimale representatie van de hash
    return hash_object.hexdigest()