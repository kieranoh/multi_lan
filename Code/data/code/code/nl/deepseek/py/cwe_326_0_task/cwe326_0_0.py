from Crypto.PublicKey import RSA
from Crypto.PublicKey.RSA import RsaKey

def create_private_key() -> str:
    """Genereer een privésleutel voor RSA, exporteer deze in het PEM-formaat en geef deze terug als een string.

    Returns:
        str: De RSA privésleutel in PEM-formaat."""
    # Genereer een RSA sleutelpaar met een standaard grootte van 2048 bits
    key: RsaKey = RSA.generate(2048)
    
    # Exporteer de privésleutel naar PEM-formaat als bytes
    private_key_pem: bytes = key.export_key(format='PEM')
    
    # Decodeer de bytes naar een string en retourneer
    return private_key_pem.decode('utf-8')