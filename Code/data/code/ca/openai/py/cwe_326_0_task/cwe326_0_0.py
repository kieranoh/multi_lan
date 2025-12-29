from Crypto.PublicKey import RSA

def create_private_key() -> str:
    """Genera una clau RSA privada, exporta-la utilitzant el format PEM i retorna-la com una cadena.

    Returns:
        str: La clau privada RSA en format PEM."""
    key = RSA.generate(2048)  # Genera una clau RSA de 2048 bits
    private_key = key.export_key()  # Exporta la clau privada en format PEM
    return private_key.decode('utf-8')  # Retorna la clau com a cadena