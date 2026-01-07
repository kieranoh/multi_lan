from Crypto.PublicKey import RSA
from Crypto.PublicKey.RSA import RsaKey


def create_private_key() -> str:
    """Generera en privat RSA-nyckel, exportera den med PEM-formatet och returnera den som en sträng.

    Returns:
        str: Den privata RSA-nyckeln i PEM-format."""
    # Generera en 2048-bitars RSA-nyckel
    key: RsaKey = RSA.generate(2048)
    
    # Exportera nyckeln i PEM-format som en sträng
    private_key_pem: str = key.export_key().decode('utf-8')
    
    return private_key_pem