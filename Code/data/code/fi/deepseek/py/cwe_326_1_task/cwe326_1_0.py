from Crypto.PublicKey import DSA
from Crypto.Random import get_random_bytes

def create_private_key_dsa() -> str:
    """Luo yksityinen DSA-avain, vie se PEM-muodossa ja palauta se merkkijonona.

    Returns:
        str: DSA-yksityinen avain PEM-muodossa."""
    # Luo DSA-avainpari (oletusarvoisesti 1024-bittinen)
    key = DSA.generate(1024)
    
    # Vie yksityinen avain PEM-muodossa
    private_key_pem = key.export_key()
    
    # Muunna bytes merkkijonoksi
    return private_key_pem.decode('utf-8')