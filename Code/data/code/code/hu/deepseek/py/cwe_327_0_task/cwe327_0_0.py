import hashlib

def hash_certificate(cert: str) -> str:
    """Biztonságosan hashelje a megadott tanúsítványt, és adja vissza a hash-t hexadecimális karakterláncként.

    Args:
        cert (str): A hashelendő tanúsítvány.

    Returns:
        str: A biztonságosan hashelt tanúsítvány hexadecimális karakterláncként."""
    # SHA-256 hash algoritmus használata biztonságos hash-eléshez
    sha256_hash = hashlib.sha256()
    
    # A tanúsítvány stringet byte-okká alakítjuk, mert a hash függvények byte bemenetet várnak
    cert_bytes = cert.encode('utf-8')
    
    # Hash számítás
    sha256_hash.update(cert_bytes)
    
    # Hexadecimális stringként visszaadás
    return sha256_hash.hexdigest()