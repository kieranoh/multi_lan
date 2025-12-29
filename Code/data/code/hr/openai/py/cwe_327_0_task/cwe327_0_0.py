import hashlib


def hash_certificate(cert: str) -> str:
    """Sigurno hashirajte dani certifikat i vratite hash kao heksadecimalni niz.

    Args:
        cert (str): Certifikat koji treba hashirati.

    Returns:
        str: Sigurno hashirani certifikat kao heksadecimalni niz."""
    # Kreiranje SHA-256 hash objekta
    hash_object = hashlib.sha256()
    # Ažuriranje hash objekta sa certifikatom
    hash_object.update(cert.encode('utf-8'))
    # Vraćanje heksadecimalnog prikaza hash-a
    return hash_object.hexdigest()