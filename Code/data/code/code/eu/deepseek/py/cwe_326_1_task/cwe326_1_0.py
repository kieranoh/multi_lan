from Crypto.PublicKey import DSA
from Crypto.Random import get_random_bytes


def create_private_key_dsa() -> str:
    """Sortu DSA gako pribatu bat, esportatu PEM formatuan, eta itzuli string gisa.

    Returns:
        str: DSA gako pribatuaren PEM formatuan.
    """
    # Sortu DSA gako pribatu bat 2048 biteko tamainarekin
    key = DSA.generate(2048)
    
    # Esportatu gakoa PEM formatuan string gisa
    private_key_pem = key.export_key(format='PEM')
    
    # Dekodetu bytes-etik string-era beharrezkoa bada
    if isinstance(private_key_pem, bytes):
        private_key_pem = private_key_pem.decode('utf-8')
    
    return private_key_pem