import hashlib


def hash_certificate(cert: str) -> str:
    """Esegui l'hashing del certificato fornito in modo sicuro e restituisci l'hash come stringa esadecimale.

    Args:
        cert (str): Il certificato da sottoporre a hashing.

    Returns:
        str: Il certificato sottoposto a hashing in modo sicuro come stringa esadecimale."""
    # Converti la stringa del certificato in bytes
    cert_bytes = cert.encode('utf-8')
    
    # Crea un oggetto hash SHA-256 (sicuro e ampiamente utilizzato)
    hash_object = hashlib.sha256(cert_bytes)
    
    # Ottieni l'hash come stringa esadecimale
    hex_digest = hash_object.hexdigest()
    
    return hex_digest