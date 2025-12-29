from typing import Tuple
from Crypto.Cipher import AES, DES
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
    # Escolha fixa do algoritmo AES (128 bits = 16 bytes)
    # A documentação diz para escolher apenas um algoritmo e não baseado no comprimento da chave
    # Vou escolher AES-128 que requer 16 bytes de chave
    algorithm = "AES"
    key_length = 16  # 16 bytes = 128 bits para AES
    
    # Usar os primeiros key_length bytes da chave fornecida
    encryption_key = key[:key_length]
    
    # Gerar IV do tamanho apropriado para o bloco do algoritmo escolhido
    # AES tem tamanho de bloco de 16 bytes
    iv = get_random_bytes(16)
    
    # Criar cifra no modo CBC
    if algorithm == "AES":
        cipher = AES.new(encryption_key, AES.MODE_CBC, iv)
    elif algorithm == "DES":
        cipher = DES.new(encryption_key, DES.MODE_CBC, iv)
    else:
        raise ValueError(f"Algoritmo não suportado: {algorithm}")
    
    # Aplicar padding aos dados e encriptar
    # AES tem tamanho de bloco de 16 bytes
    padded_data = pad(data, 16)
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, encryption_key