from Crypto.PublicKey import DSA

def create_private_key_dsa() -> str:
    """Generálj egy privát DSA kulcsot, exportáld PEM formátumban, és térj vissza vele egy stringként.

    Visszatér:
        str: A DSA privát kulcs PEM formátumban."""
    key = DSA.generate(2048)
    return key.export_key(format='PEM').decode('utf-8')