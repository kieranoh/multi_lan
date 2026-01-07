from Crypto.PublicKey import RSA


def create_private_key() -> str:
    """Sortu RSA gako pribatu bat, esportatu PEM formatuan, eta itzuli string gisa.

    Returns:
        str: RSA gako pribatuaren PEM formatuan."""
    key = RSA.generate(2048)
    private_key_pem = key.export_key(format='PEM')
    return private_key_pem.decode('utf-8')