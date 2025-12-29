from Crypto.PublicKey import DSA
from Crypto.Random import get_random_bytes

def create_private_key_dsa() -> str:
    """Generera en privat DSA-nyckel, exportera den med PEM-formatet och returnera den som en sträng.

    Returns:
        str: Den privata DSA-nyckeln i PEM-format."""
    # Generera en DSA-nyckel med standardparametrar (1024-bitars)
    key = DSA.generate(1024)
    
    # Exportera nyckeln i PEM-format
    private_key_pem = key.export_key(format='PEM')
    
    # Konvertera bytes till sträng om nödvändigt
    if isinstance(private_key_pem, bytes):
        return private_key_pem.decode('utf-8')
    return private_key_pem