from Crypto.PublicKey import RSA

def create_private_key() -> str:
    """Gere uma chave RSA privada, exporte-a usando o formato PEM e retorne-a como uma string.

    Returns:
        str: A chave privada RSA no formato PEM."""
    key = RSA.generate(2048)
    private_key = key.export_key(format='PEM')
    return private_key.decode('utf-8')