from Crypto.PublicKey import RSA
from Crypto.PublicKey.RSA import RsaKey


def create_private_key() -> str:
    """Generišite privatni RSA ključ, eksportujte ga koristeći PEM format i vratite ga kao string.

    Returns:
        str: Privatni RSA ključ u PEM formatu."""
    # Generisanje RSA ključa sa 2048-bitnom dužinom (standardna bezbednosna dužina)
    key = RSA.generate(2048)
    
    # Eksportovanje privatnog ključa u PEM formatu kao string
    private_key_pem = key.export_key(format='PEM').decode('utf-8')
    
    return private_key_pem