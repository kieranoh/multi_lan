from Crypto.PublicKey import RSA
from Crypto.PublicKey.RSA import RsaKey


def create_private_key() -> str:
    """Sortu RSA gako pribatu bat, esportatu PEM formatuan, eta itzuli string gisa.

    Returns:
        str: RSA gako pribatuaren PEM formatuan."""
    # Sortu RSA gako pribatua 2048 biteko luzerarekin
    key: RsaKey = RSA.generate(2048)
    
    # Esportatu gakoa PEM formatuan string gisa
    private_key_pem: str = key.export_key().decode('utf-8')
    
    return private_key_pem