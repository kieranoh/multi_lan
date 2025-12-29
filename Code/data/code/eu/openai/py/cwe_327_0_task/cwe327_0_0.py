import hashlib


def hash_certificate(cert: str) -> str:
    """Ziurtagiri emandako segurtasunez hashatu eta hash-a hexadigoko string gisa itzuli.

    Args:
        cert (str): Hashatu beharreko ziurtagiria.

    Returns:
        str: Segurtasunez hashatutako ziurtagiria hexadigoko string gisa."""
    hash_object = hashlib.sha256(cert.encode())
    hex_dig = hash_object.hexdigest()
    return hex_dig