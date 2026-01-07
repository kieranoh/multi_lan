from Crypto.PublicKey import RSA
from Crypto.PublicKey.RSA import RsaKey


def create_private_key() -> str:
    """Luo yksityinen RSA-avain, vie se PEM-muodossa ja palauta se merkkijonona.

    Returns:
        str: RSA-yksityinen avain PEM-muodossa."""
    # Luo 2048-bittinen RSA-avainpari
    key: RsaKey = RSA.generate(2048)
    
    # Vie yksityinen avain PEM-muodossa
    private_key_pem: str = key.export_key().decode('utf-8')
    
    return private_key_pem