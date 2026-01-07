from Crypto.PublicKey import DSA
from Crypto.Random import get_random_bytes

def create_private_key_dsa() -> str:
    """Gere uma chave DSA privada, exporte-a usando o formato PEM e retorne-a como uma string.

    Returns:
        str: A chave privada DSA no formato PEM."""
    # Gerar parâmetros DSA (p, q, g)
    key = DSA.generate(2048)
    
    # Exportar a chave privada no formato PEM
    private_key_pem = key.export_key(format='PEM')
    
    # Decodificar bytes para string se necessário
    if isinstance(private_key_pem, bytes):
        private_key_pem = private_key_pem.decode('utf-8')
    
    return private_key_pem