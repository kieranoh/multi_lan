from Crypto.PublicKey import RSA

def create_private_key() -> str:
    """Genera una clave RSA privada, expórtala usando el formato PEM y devuélvela como una cadena.

    Returns:
        str: La clave privada RSA en formato PEM."""
    key = RSA.generate(2048)
    private_key = key.export_key(format='PEM')
    return private_key.decode('utf-8')