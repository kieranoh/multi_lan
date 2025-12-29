import hashlib


def hash_certificate(cert: str) -> str:
    """Biztonságosan hashelje a megadott tanúsítványt, és adja vissza a hash-t hexadecimális karakterláncként.

    Args:
        cert (str): A hashelendő tanúsítvány.

    Returns:
        str: A biztonságosan hashelt tanúsítvány hexadecimális karakterláncként."""
    # Használjunk SHA-256 algoritmust a tanúsítvány hashelésére
    hash_object = hashlib.sha256(cert.encode())
    # Visszatérünk a hash hexadecimális reprezentációjával
    return hash_object.hexdigest()