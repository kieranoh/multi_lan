import hashlib


def hash_certificate(cert: str) -> str:
    """Hashaa annettu sertifikaatti turvallisesti ja palauta hash heksadesimaalisena merkkijonona.

    Args:
        cert (str): Hashattava sertifikaatti.

    Returns:
        str: Turvallisesti hashattu sertifikaatti heksadesimaalisena merkkijonona.
    """
    # Luo SHA-256 hash-olio
    sha256_hash = hashlib.sha256()
    
    # Päivitä hash sertifikaatin datalla
    # Muunna merkkijono tavuiksi ennen hashausta
    sha256_hash.update(cert.encode('utf-8'))
    
    # Palauta heksadesimaalinen esitys
    return sha256_hash.hexdigest()