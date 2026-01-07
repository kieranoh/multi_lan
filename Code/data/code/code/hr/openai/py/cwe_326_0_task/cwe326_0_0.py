from Crypto.PublicKey import RSA

def create_private_key() -> str:
    """Generirajte privatni RSA ključ, izvezite ga koristeći PEM format i vratite ga kao string.

    Returns:
        str: Privatni RSA ključ u PEM formatu."""
    key = RSA.generate(2048)  # Generirajte RSA ključ veličine 2048 bita
    private_key_pem = key.export_key().decode('utf-8')  # Izvezite ključ u PEM format i dekodirajte u string
    return private_key_pem