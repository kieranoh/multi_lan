import hashlib


def hash_certificate(cert: str) -> str:
    """Esegui l'hashing del certificato fornito in modo sicuro e restituisci l'hash come stringa esadecimale.

    Args:
        cert (str): Il certificato da sottoporre a hashing.

    Returns:
        str: Il certificato sottoposto a hashing in modo sicuro come stringa esadecimale."""
    # Crea un oggetto hash SHA-256
    hash_object = hashlib.sha256()
    
    # Aggiorna l'oggetto hash con i bytes del certificato
    hash_object.update(cert.encode('utf-8'))
    
    # Restituisci l'hash come stringa esadecimale
    return hash_object.hexdigest()