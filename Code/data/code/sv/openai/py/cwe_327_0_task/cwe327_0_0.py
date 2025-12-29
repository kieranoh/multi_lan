import hashlib


def hash_certificate(cert: str) -> str:
    """Hasha det angivna certifikatet på ett säkert sätt och returnera hashvärdet som en hexadecimalt sträng.

    Args:
        cert (str): Certifikatet som ska hashas.

    Returns:
        str: Det säkert hashade certifikatet som en hexadecimalt sträng."""
    
    # Skapa en hash-objekt med SHA-256 algoritmen
    hash_object = hashlib.sha256()
    
    # Uppdatera hash-objektet med certifikatets bytes
    hash_object.update(cert.encode('utf-8'))
    
    # Beräkna den hexadecimala representationen av hashvärdet
    hashed_cert = hash_object.hexdigest()
    
    return hashed_cert