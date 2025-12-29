from Crypto.PublicKey import DSA
from Crypto.Random import get_random_bytes

def create_private_key_dsa() -> str:
    """Genereer een privé DSA-sleutel, exporteer deze in PEM-indeling en retourneer deze als een string.

    Returns:
        str: De DSA privé-sleutel in PEM-indeling."""
    # Genereer een nieuwe DSA-sleutel met standaard grootte (1024 bits)
    key = DSA.generate(1024)
    
    # Exporteer de privé-sleutel naar PEM-indeling
    private_key_pem = key.export_key(format='PEM')
    
    # Retourneer als string (decodeer bytes naar string indien nodig)
    if isinstance(private_key_pem, bytes):
        return private_key_pem.decode('utf-8')
    return private_key_pem