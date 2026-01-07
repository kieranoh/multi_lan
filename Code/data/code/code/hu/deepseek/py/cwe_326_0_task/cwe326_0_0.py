from Crypto.PublicKey import RSA
from Crypto.PublicKey.RSA import RsaKey

def create_private_key() -> str:
    """Generálj egy privát RSA kulcsot, exportáld PEM formátumban, és térj vissza egy stringgel.

    Visszatér:
        str: Az RSA privát kulcs PEM formátumban."""
    key: RsaKey = RSA.generate(2048)
    private_key_pem: bytes = key.export_key(format='PEM')
    return private_key_pem.decode('utf-8')