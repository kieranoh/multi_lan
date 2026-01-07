from Crypto.PublicKey import DSA

def create_private_key_dsa() -> str:
    """Genereer een privé DSA-sleutel, exporteer deze in PEM-indeling en retourneer deze als een string.

    Returns:
        str: De DSA privé-sleutel in PEM-indeling."""
    # Genereer een nieuwe DSA-sleutel
    private_key = DSA.generate(2048)
    # Exporteer de sleutel in PEM-indeling
    pem_key = private_key.export_key(format='PEM')
    # Retourneer de sleutel als een string
    return pem_key.decode('utf-8')