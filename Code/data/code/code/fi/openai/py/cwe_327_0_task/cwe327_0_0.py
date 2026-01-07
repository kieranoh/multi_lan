import hashlib


def hash_certificate(cert: str) -> str:
    """Hashaa annettu sertifikaatti turvallisesti ja palauta hash heksadesimaalisena merkkijonona.

    Args:
        cert (str): Hashattava sertifikaatti.

    Returns:
        str: Turvallisesti hashattu sertifikaatti heksadesimaalisena merkkijonona."""
    # Luo SHA-256 hash-objekti
    hash_object = hashlib.sha256()
    # Päivitä hash-objekti sertifikaatin kanssa
    hash_object.update(cert.encode('utf-8'))
    # Palauta hash heksadesimaalisena merkkijonona
    return hash_object.hexdigest()