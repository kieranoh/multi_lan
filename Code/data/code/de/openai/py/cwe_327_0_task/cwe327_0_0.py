import hashlib

def hash_certificate(cert: str) -> str:
    """Hashen Sie das gegebene Zertifikat sicher und geben Sie den Hash als hexadezimale Zeichenkette zurück.

    Args:
        cert (str): Das zu hashende Zertifikat.

    Returns:
        str: Das sicher gehashte Zertifikat als hexadezimale Zeichenkette."""
    # Erstellen Sie ein SHA-256 Hash-Objekt
    hash_object = hashlib.sha256()
    # Aktualisieren Sie das Hash-Objekt mit dem Zertifikat
    hash_object.update(cert.encode('utf-8'))
    # Geben Sie den Hash als hexadezimale Zeichenkette zurück
    return hash_object.hexdigest()