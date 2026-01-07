from Crypto.PublicKey import RSA

def create_private_key() -> str:
    """Generera en privat RSA-nyckel, exportera den med PEM-formatet och returnera den som en sträng.

    Returns:
        str: Den privata RSA-nyckeln i PEM-format."""
    key = RSA.generate(2048)
    private_key = key.export_key()
    return private_key.decode('utf-8')