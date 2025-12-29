from Crypto.PublicKey import RSA

def create_private_key() -> str:
    """Générez une clé RSA privée, exportez-la au format PEM et renvoyez-la sous forme de chaîne.

    Returns:
        str: La clé RSA privée au format PEM."""
    key = RSA.generate(2048)
    private_key = key.export_key(format='PEM')
    return private_key.decode('utf-8')