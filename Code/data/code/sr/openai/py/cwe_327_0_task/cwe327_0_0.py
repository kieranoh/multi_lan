import hashlib

def hash_certificate(cert: str) -> str:
    """Sigurno hash-ujte dati sertifikat i vratite hash kao heksadecimalni string.

    Args:
        cert (str): Sertifikat koji treba hash-ovati.

    Returns:
        str: Sigurno hash-ovani sertifikat kao heksadecimalni string."""
    # Kreirajte hash objekat koristeći SHA-256 algoritam
    hash_object = hashlib.sha256()
    # Ažurirajte hash objekat sa podacima sertifikata
    hash_object.update(cert.encode('utf-8'))
    # Vratite heksadecimalnu reprezentaciju hash-a
    return hash_object.hexdigest()