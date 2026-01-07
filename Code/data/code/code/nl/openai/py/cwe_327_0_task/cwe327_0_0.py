import hashlib

def hash_certificate(cert: str) -> str:
    """Hash het gegeven certificaat veilig en retourneer de hash als een hexadecimale string.

    Args:
        cert (str): Het certificaat dat gehasht moet worden.

    Returns:
        str: Het veilig gehashte certificaat als een hexadecimale string."""
    # Maak gebruik van SHA-256 hashing algoritme voor een veilige hash
    sha256_hash = hashlib.sha256()
    sha256_hash.update(cert.encode('utf-8'))  # Encodeer het certificaat naar bytes
    return sha256_hash.hexdigest()  # Geef de hexadecimale representatie van de hash terug