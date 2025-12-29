import hashlib


def hash_certificate(cert: str) -> str:
    """Hasha det angivna certifikatet på ett säkert sätt och returnera hashvärdet som en hexadecimalt sträng.

    Args:
        cert (str): Certifikatet som ska hashas.

    Returns:
        str: Det säkert hashade certifikatet som en hexadecimalt sträng.
    """
    # Konvertera certifikatsträngen till bytes
    cert_bytes = cert.encode('utf-8')
    
    # Skapa en SHA-256 hash av certifikatet
    hash_object = hashlib.sha256(cert_bytes)
    
    # Returnera hexadecimal representation av hashen
    return hash_object.hexdigest()