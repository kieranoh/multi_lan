import hashlib


def hash_certificate(cert: str) -> str:
    """Sigurno hashirajte dani certifikat i vratite hash kao heksadecimalni niz.

    Args:
        cert (str): Certifikat koji treba hashirati.

    Returns:
        str: Sigurno hashirani certifikat kao heksadecimalni niz.
    """
    # Koristimo SHA-256 za sigurno hashiranje
    sha256_hash = hashlib.sha256()
    
    # Enkodiraj certifikat u bytes prije hashiranja
    sha256_hash.update(cert.encode('utf-8'))
    
    # Vrati heksadecimalni prikaz hash vrijednosti
    return sha256_hash.hexdigest()