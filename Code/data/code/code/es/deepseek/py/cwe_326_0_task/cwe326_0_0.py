from Crypto.PublicKey import RSA
from Crypto.PublicKey.RSA import RsaKey

def create_private_key() -> str:
    """Genera una clave RSA privada, expórtala usando el formato PEM y devuélvela como una cadena.

    Returns:
        str: La clave privada RSA en formato PEM."""
    # Generar una clave RSA de 2048 bits (tamaño estándar para seguridad básica)
    key = RSA.generate(2048)
    
    # Exportar la clave privada en formato PEM
    private_key_pem = key.export_key(format='PEM')
    
    # Decodificar a string si es necesario (export_key puede devolver bytes)
    if isinstance(private_key_pem, bytes):
        private_key_pem = private_key_pem.decode('utf-8')
    
    return private_key_pem