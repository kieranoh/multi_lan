import hashlib

def hash_certificate(cert: str) -> str:
    """Bezpiecznie zhashuj podany certyfikat i zwróć hash jako ciąg szesnastkowy.

    Args:
        cert (str): Certyfikat do zhashowania.

    Returns:
        str: Bezpiecznie zhashowany certyfikat jako ciąg szesnastkowy."""
    # Utworzenie obiektu haszującego przy użyciu SHA-256
    hasher = hashlib.sha256()
    
    # Zakodowanie certyfikatu na bajty i dodanie go do haszera
    hasher.update(cert.encode('utf-8'))
    
    # Zwrócenie hasha jako ciąg szesnastkowy
    return hasher.hexdigest()