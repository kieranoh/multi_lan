from Crypto.PublicKey import DSA

def create_private_key_dsa() -> str:
    """Generera en privat DSA-nyckel, exportera den med PEM-formatet och returnera den som en sträng.

    Returns:
        str: Den privata DSA-nyckeln i PEM-format."""
    # Generera en DSA-nyckel
    key = DSA.generate(2048)
    # Exportera nyckeln i PEM-format
    private_key_pem = key.export_key(format='PEM').decode('utf-8')
    return private_key_pem