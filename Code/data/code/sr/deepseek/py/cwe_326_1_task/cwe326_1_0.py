from Crypto.PublicKey import DSA
from Crypto.Random import get_random_bytes

def create_private_key_dsa() -> str:
    """Generišite privatni DSA ključ, eksportujte ga koristeći PEM format i vratite ga kao string.

    Returns:
        str: Privatni DSA ključ u PEM formatu."""
    # Generišemo DSA ključ sa standardnom veličinom od 1024 bita
    key = DSA.generate(1024)
    
    # Eksportujemo privatni ključ u PEM formatu
    private_key_pem = key.export_key(format='PEM')
    
    # Vraćamo kao string (export_key() već vraća bytes, pa dekodiramo u string)
    return private_key_pem.decode('utf-8')