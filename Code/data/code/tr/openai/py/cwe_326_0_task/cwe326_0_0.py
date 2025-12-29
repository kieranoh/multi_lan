from Crypto.PublicKey import RSA


def create_private_key() -> str:
    """Özel bir RSA anahtarı oluşturun, PEM formatında dışa aktarın ve bir dize olarak döndürün.

    Returns:
        str: PEM formatındaki RSA özel anahtarı."""
    key = RSA.generate(2048)
    private_key_pem = key.export_key(format='PEM')
    return private_key_pem.decode('utf-8')