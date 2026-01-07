from Crypto.PublicKey import RSA

def create_private_key() -> str:
    """Genereer een privésleutel voor RSA, exporteer deze in het PEM-formaat en geef deze terug als een string.

    Returns:
        str: De RSA privésleutel in PEM-formaat."""
    private_key = RSA.generate(2048)  # Genereer een RSA-sleutel van 2048 bits
    pem_key = private_key.export_key()  # Exporteer de privésleutel in PEM-formaat
    return pem_key.decode('utf-8')  # Geef de sleutel terug als een string