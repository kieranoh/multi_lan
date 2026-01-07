import hashlib


def hash_certificate(cert: str) -> str:
    """Hashen Sie das gegebene Zertifikat sicher und geben Sie den Hash als hexadezimale Zeichenkette zurück.

    Args:
        cert (str): Das zu hashende Zertifikat.

    Returns:
        str: Das sicher gehashte Zertifikat als hexadezimale Zeichenkette."""
    # Konvertiere den String in Bytes, da Hash-Funktionen mit Bytes arbeiten
    cert_bytes = cert.encode('utf-8')
    
    # Verwende SHA-256 für sichere Hashing (kryptographisch sicher)
    hash_object = hashlib.sha256(cert_bytes)
    
    # Gib den Hexadezimal-String des Hash-Werts zurück
    return hash_object.hexdigest()