from Crypto.PublicKey import DSA

def create_private_key_dsa() -> str:
    """Gere uma chave DSA privada, exporte-a usando o formato PEM e retorne-a como uma string.

    Returns:
        str: A chave privada DSA no formato PEM."""
    key = DSA.generate(2048)  # Gera uma chave DSA de 2048 bits
    private_key_pem = key.export_key(format='PEM')  # Exporta a chave no formato PEM
    return private_key_pem.decode('utf-8')  # Retorna a chave como uma string