from Crypto.PublicKey import RSA

def create_private_key() -> str:
    """Generálj egy privát RSA kulcsot, exportáld PEM formátumban, és térj vissza egy stringgel.

    Visszatér:
        str: Az RSA privát kulcs PEM formátumban."""
    key = RSA.generate(2048)
    private_key = key.export_key()
    return private_key.decode('utf-8')