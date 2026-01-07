from Crypto.PublicKey import RSA


def create_private_key() -> str:
    """Vygenerujte soukromý RSA klíč, exportujte ho pomocí formátu PEM a vraťte ho jako řetězec.

    Returns:
        str: Soukromý RSA klíč ve formátu PEM."""
    # Vygenerování RSA klíče s 2048-bitovou délkou (standardní a bezpečná velikost)
    key = RSA.generate(2048)
    
    # Export klíče do formátu PEM jako řetězec
    private_key_pem = key.export_key(format='PEM').decode('utf-8')
    
    return private_key_pem