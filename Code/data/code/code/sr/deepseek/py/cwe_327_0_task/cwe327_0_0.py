import hashlib


def hash_certificate(cert: str) -> str:
    """Sigurno hash-ujte dati sertifikat i vratite hash kao heksadecimalni string.

    Args:
        cert (str): Sertifikat koji treba hash-ovati.

    Returns:
        str: Sigurno hash-ovani sertifikat kao heksadecimalni string.
    """
    # Koristimo SHA-256 algoritam za sigurno hash-ovanje
    # Prvo kodiramo string u bajtove jer hash funkcije rade sa bajtovima
    cert_bytes = cert.encode('utf-8')
    
    # Kreiraj SHA-256 hash objekat
    hash_object = hashlib.sha256()
    
    # Ažuriraj hash objekat sa bajtovima sertifikata
    hash_object.update(cert_bytes)
    
    # Dobij heksadecimalni string od hash vrednosti
    hex_dig = hash_object.hexdigest()
    
    return hex_dig