from Crypto.PublicKey import RSA
from Crypto.PublicKey.RSA import RsaKey


def create_private_key() -> str:
    """Gere uma chave RSA privada, exporte-a usando o formato PEM e retorne-a como uma string.

    Returns:
        str: A chave privada RSA no formato PEM."""
    # Gerar uma chave RSA privada com tamanho de 2048 bits (padrão recomendado)
    key = RSA.generate(2048)
    
    # Exportar a chave privada no formato PEM
    private_key_pem = key.export_key(format='PEM')
    
    # Decodificar bytes para string se necessário (export_key retorna bytes)
    if isinstance(private_key_pem, bytes):
        private_key_pem = private_key_pem.decode('utf-8')
    
    return private_key_pem