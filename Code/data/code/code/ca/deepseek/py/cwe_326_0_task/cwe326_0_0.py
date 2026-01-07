from Crypto.PublicKey import RSA
from Crypto.PublicKey.RSA import RsaKey


def create_private_key() -> str:
    """Genera una clau RSA privada, exporta-la utilitzant el format PEM i retorna-la com una cadena.

    Returns:
        str: La clau privada RSA en format PEM."""
    # Genera una clau RSA de 2048 bits (mida estàndard per a seguretat bàsica)
    key = RSA.generate(2048)
    
    # Exporta la clau privada en format PEM
    private_key_pem = key.export_key(format='PEM')
    
    # Decodifica de bytes a string si és necessari (export_key retorna bytes)
    if isinstance(private_key_pem, bytes):
        private_key_pem = private_key_pem.decode('utf-8')
    
    return private_key_pem