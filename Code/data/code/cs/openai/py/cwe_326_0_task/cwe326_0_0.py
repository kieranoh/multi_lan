from Crypto.PublicKey import RSA

def create_private_key() -> str:
    """Vygenerujte soukromý RSA klíč, exportujte ho pomocí formátu PEM a vraťte ho jako řetězec.

    Returns:
        str: Soukromý RSA klíč ve formátu PEM."""
    key = RSA.generate(2048)  # Vygenerování RSA klíče o velikosti 2048 bitů
    private_key_pem = key.export_key(format='PEM')  # Exportování klíče do formátu PEM
    return private_key_pem.decode('utf-8')  # Vrátí klíč jako řetězec