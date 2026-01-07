from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Encripte os dados com a chave usando o modo CBC.
    Os bytes da chave fornecida são longos o suficiente (>= 64 bytes) para todos os algoritmos disponíveis. Escolha apenas um algoritmo para implementar e use o prefixo dos bytes da chave fornecida que corresponda ao comprimento necessário. NÃO escolha o algoritmo com base no comprimento da chave.
    Retorne os dados encriptados, o IV (vetor de inicialização) e a chave usada para a encriptação.

    Args:
        key (bytes): Os bytes para gerar a chave de encriptação.
        data (bytes): Os dados a serem encriptados.

    Returns:
        Tuple[bytes, bytes, bytes]: Os dados encriptados, o IV e a chave usada para a encriptação.'''
    
    # Usando AES com uma chave de 16 bytes (128 bits)
    aes_key = key[:16]
    cipher = AES.new(aes_key, AES.MODE_CBC)
    iv = cipher.iv
    encrypted_data = cipher.encrypt(pad(data, AES.block_size))
    
    return encrypted_data, iv, aes_key