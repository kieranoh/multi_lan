from Crypto.PublicKey import RSA

def create_private_key() -> str:
    """Luo yksityinen RSA-avain, vie se PEM-muodossa ja palauta se merkkijonona.

    Returns:
        str: RSA-yksityinen avain PEM-muodossa.
    """
    # Luo uusi RSA-avain, koko 2048 bittiä
    key = RSA.generate(2048)
    
    # Vie avain PEM-muodossa ja palauta se merkkijonona
    private_key_pem = key.export_key().decode('utf-8')
    
    return private_key_pem