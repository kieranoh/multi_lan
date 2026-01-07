from Crypto.PublicKey import DSA

def create_private_key_dsa() -> str:
    """Vygenerujte soukromý DSA klíč, exportujte ho pomocí formátu PEM a vraťte ho jako řetězec.

    Returns:
        str: Soukromý DSA klíč ve formátu PEM."""
    
    # Generování DSA soukromého klíče
    key = DSA.generate(2048)
    
    # Exportování klíče do formátu PEM
    private_key_pem = key.export_key(format='PEM')
    
    return private_key_pem.decode('utf-8')