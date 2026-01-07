from Crypto.PublicKey import DSA
from Crypto.Random import get_random_bytes

def create_private_key_dsa() -> str:
    """Genera una clau privada DSA, exporta-la utilitzant el format PEM i retorna-la com una cadena.

    Returns:
        str: La clau privada DSA en format PEM."""
    # Generar una clau DSA de 2048 bits (mida estàndard actual)
    key = DSA.generate(2048)
    
    # Exportar la clau privada en format PEM
    private_key_pem = key.export_key(format='PEM')
    
    # Decodificar de bytes a string si és necessari (ja que export_key retorna bytes)
    if isinstance(private_key_pem, bytes):
        private_key_pem = private_key_pem.decode('utf-8')
    
    return private_key_pem