from Crypto.PublicKey import DSA
from Crypto.Random import get_random_bytes

def create_private_key_dsa() -> str:
    """Generálj egy privát DSA kulcsot, exportáld PEM formátumban, és térj vissza vele egy stringként.

    Visszatér:
        str: A DSA privát kulcs PEM formátumban."""
    # Generálj egy 2048 bites DSA kulcsot
    key = DSA.generate(2048)
    
    # Exportáld a privát kulcsot PEM formátumban
    private_key_pem = key.export_key(format='PEM')
    
    # Dekódold bytes-ból stringgé, ha szükséges
    if isinstance(private_key_pem, bytes):
        private_key_pem = private_key_pem.decode('utf-8')
    
    return private_key_pem