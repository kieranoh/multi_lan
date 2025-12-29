from Crypto.PublicKey import DSA
from Crypto.Random import get_random_bytes

def create_private_key_dsa() -> str:
    """Generirajte privatni DSA ključ, izvezite ga koristeći PEM format i vratite ga kao string.

    Returns:
        str: Privatni DSA ključ u PEM formatu."""
    # Generiraj DSA ključ s veličinom od 2048 bita
    key = DSA.generate(2048)
    
    # Izvezi privatni ključ u PEM formatu
    private_key_pem = key.export_key(format='PEM')
    
    # Dekodiraj iz bytes u string ako je potrebno
    if isinstance(private_key_pem, bytes):
        private_key_pem = private_key_pem.decode('utf-8')
    
    return private_key_pem