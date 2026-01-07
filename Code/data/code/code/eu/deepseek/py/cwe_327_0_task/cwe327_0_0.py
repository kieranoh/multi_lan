import hashlib


def hash_certificate(cert: str) -> str:
    """Ziurtagiri emandako segurtasunez hashatu eta hash-a hexadigoko string gisa itzuli.

    Args:
        cert (str): Hashatu beharreko ziurtagiria.

    Returns:
        str: Segurtasunez hashatutako ziurtagiria hexadigoko string gisa.
    """
    # Ziurtatu sarrera string bat dela eta hutsik ez dagoela
    if not isinstance(cert, str):
        raise TypeError("cert parametroa string bat izan behar da")
    
    if not cert:
        raise ValueError("cert parametroa ezin da hutsa izan")
    
    # SHA-256 hash funtzioa erabili segurtasun handiagoa lortzeko
    hash_object = hashlib.sha256(cert.encode('utf-8'))
    
    # Hexadezimal formatuan itzuli
    return hash_object.hexdigest()