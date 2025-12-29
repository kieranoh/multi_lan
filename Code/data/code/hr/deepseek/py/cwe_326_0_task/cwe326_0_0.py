from Crypto.PublicKey import RSA
from Crypto.PublicKey.RSA import RsaKey

def create_private_key() -> str:
    """Generirajte privatni RSA ključ, izvezite ga koristeći PEM format i vratite ga kao string.

    Returns:
        str: Privatni RSA ključ u PEM formatu."""
    # Generiraj RSA ključ s 2048-bitnom duljinom (standardna sigurnosna duljina)
    key = RSA.generate(2048)
    
    # Izvezi privatni ključ u PEM formatu
    private_key_pem = key.export_key(format='PEM')
    
    # Dekodiraj iz bytes u string ako je potrebno
    if isinstance(private_key_pem, bytes):
        private_key_pem = private_key_pem.decode('utf-8')
    
    return private_key_pem