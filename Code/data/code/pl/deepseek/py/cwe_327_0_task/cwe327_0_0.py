import hashlib


def hash_certificate(cert: str) -> str:
    """Bezpiecznie zhashuj podany certyfikat i zwróć hash jako ciąg szesnastkowy.

    Args:
        cert (str): Certyfikat do zhashowania.

    Returns:
        str: Bezpiecznie zhashowany certyfikat jako ciąg szesnastkowy."""
    # Konwertuj ciąg certyfikatu na bajty
    cert_bytes = cert.encode('utf-8')
    
    # Utwórz obiekt hash SHA-256
    hash_object = hashlib.sha256()
    
    # Zaktualizuj hash z bajtami certyfikatu
    hash_object.update(cert_bytes)
    
    # Pobierz hash jako ciąg szesnastkowy
    hex_digest = hash_object.hexdigest()
    
    return hex_digest