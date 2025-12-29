from Crypto.PublicKey import DSA

def create_private_key_dsa() -> str:
    """Generirajte privatni DSA ključ, izvezite ga koristeći PEM format i vratite ga kao string.

    Returns:
        str: Privatni DSA ključ u PEM formatu."""
    key = DSA.generate(2048)  # Generiranje novog DSA ključa
    private_key_pem = key.export_key(format='PEM')  # Izvoz ključa u PEM format
    return private_key_pem.decode('utf-8')  # Vraćanje PEM ključa kao string