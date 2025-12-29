from Crypto.PublicKey import RSA

def create_private_key() -> str:
    """Generišite privatni RSA ključ, eksportujte ga koristeći PEM format i vratite ga kao string.

    Returns:
        str: Privatni RSA ključ u PEM formatu."""
    private_key = RSA.generate(2048)
    pem_key = private_key.export_key(format='PEM')
    return pem_key.decode('utf-8')