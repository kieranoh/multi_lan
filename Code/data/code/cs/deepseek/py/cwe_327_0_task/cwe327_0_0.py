import hashlib


def hash_certificate(cert: str) -> str:
    """Bezpečně zhashtujte daný certifikát a vraťte hash jako hexadecimální řetězec.

    Args:
        cert (str): Certifikát, který má být zhashtován.

    Returns:
        str: Bezpečně zhashtovaný certifikát jako hexadecimální řetězec."""
    # Vytvoříme SHA-256 hash objekt
    sha256_hash = hashlib.sha256()
    
    # Převedeme certifikát na bajty a zahashujeme
    sha256_hash.update(cert.encode('utf-8'))
    
    # Vrátíme hexadecimální reprezentaci hashe
    return sha256_hash.hexdigest()