from Crypto.PublicKey import DSA
from Crypto.Random import get_random_bytes

def create_private_key_dsa() -> str:
    """Genera una clave DSA privada, expórtala usando el formato PEM y devuélvela como una cadena.

    Returns:
        str: La clave privada DSA en formato PEM."""
    # Generar parámetros DSA (tamaño de clave de 2048 bits)
    key = DSA.generate(2048)
    
    # Exportar la clave privada en formato PEM
    private_key_pem = key.export_key(format='PEM')
    
    # Decodificar a string si es necesario (export_key puede devolver bytes)
    if isinstance(private_key_pem, bytes):
        private_key_pem = private_key_pem.decode('utf-8')
    
    return private_key_pem