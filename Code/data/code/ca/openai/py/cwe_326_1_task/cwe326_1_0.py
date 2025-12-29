from Crypto.PublicKey import DSA

def create_private_key_dsa() -> str:
    """Genera una clau privada DSA, exporta-la utilitzant el format PEM i retorna-la com una cadena.

    Returns:
        str: La clau privada DSA en format PEM."""
    key = DSA.generate(2048)  # Genera una clau DSA de 2048 bits
    private_key_pem = key.export_key(format='PEM')  # Exporta la clau en format PEM
    return private_key_pem.decode('utf-8')  # Retorna la clau com una cadena