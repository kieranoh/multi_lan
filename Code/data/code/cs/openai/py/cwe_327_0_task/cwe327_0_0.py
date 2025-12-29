import hashlib

def hash_certificate(cert: str) -> str:
    """Bezpečně zhashtujte daný certifikát a vraťte hash jako hexadecimální řetězec.

    Args:
        cert (str): Certifikát, který má být zhashtován.

    Returns:
        str: Bezpečně zhashtovaný certifikát jako hexadecimální řetězec."""
    
    # Vytvoření hash objektu pomocí SHA-256
    hash_object = hashlib.sha256()
    
    # Aktualizace hash objektu s obsahem certifikátu
    hash_object.update(cert.encode('utf-8'))
    
    # Vracení hexadecimálního řetězce
    return hash_object.hexdigest()