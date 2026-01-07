from Crypto.PublicKey import DSA
from Crypto.Random import get_random_bytes


def create_private_key_dsa() -> str:
    """Vygenerujte soukromý DSA klíč, exportujte ho pomocí formátu PEM a vraťte ho jako řetězec.

    Returns:
        str: Soukromý DSA klíč ve formátu PEM."""
    # Generování DSA klíče s doporučenou velikostí 2048 bitů
    key = DSA.generate(2048)
    
    # Export klíče do formátu PEM jako řetězec
    private_key_pem = key.export_key(format='PEM')
    
    # Dekódování z bytes na string, pokud je potřeba
    if isinstance(private_key_pem, bytes):
        return private_key_pem.decode('utf-8')
    return private_key_pem