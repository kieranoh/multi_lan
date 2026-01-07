from Crypto.PublicKey import DSA

def create_private_key_dsa() -> str:
    """Sortu DSA gako pribatu bat, esportatu PEM formatuan, eta itzuli string gisa.

    Returns:
        str: DSA gako pribatuaren PEM formatuan."""
    key = DSA.generate(2048)
    private_key_pem = key.export_key(format='PEM')
    return private_key_pem.decode('utf-8')