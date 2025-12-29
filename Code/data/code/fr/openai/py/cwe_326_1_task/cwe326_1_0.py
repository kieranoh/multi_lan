from Crypto.PublicKey import DSA

def create_private_key_dsa() -> str:
    """Générez une clé DSA privée, exportez-la au format PEM et renvoyez-la sous forme de chaîne.

    Returns:
        str: La clé DSA privée au format PEM."""
    key = DSA.generate(2048)  # Génération d'une clé DSA de 2048 bits
    private_key_pem = key.export_key(format='PEM')  # Exportation de la clé au format PEM
    return private_key_pem.decode('utf-8')  # Retourner la clé sous forme de chaîne