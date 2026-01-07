from Crypto.PublicKey import DSA

def create_private_key_dsa() -> str:
    """Generišite privatni DSA ključ, eksportujte ga koristeći PEM format i vratite ga kao string.

    Returns:
        str: Privatni DSA ključ u PEM formatu."""
    private_key = DSA.generate(2048)
    pem_key = private_key.export_key(format='PEM')
    return pem_key.decode('utf-8')