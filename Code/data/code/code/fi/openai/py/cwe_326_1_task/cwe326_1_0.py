from Crypto.PublicKey import DSA

def create_private_key_dsa() -> str:
    """Luo yksityinen DSA-avain, vie se PEM-muodossa ja palauta se merkkijonona.

    Returns:
        str: DSA-yksityinen avain PEM-muodossa."""
    key = DSA.generate(2048)  # Luo DSA-yksityinen avain
    private_key_pem = key.export_key(format='PEM')  # Vie avain PEM-muodossa
    return private_key_pem.decode('utf-8')  # Palauta merkkijonona