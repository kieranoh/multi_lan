from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
import os


def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Encripte os dados com a chave usando AES e modo CBC.
    Os bytes da chave fornecida são longos o suficiente (>= 64 bytes). Use o prefixo dos bytes da chave fornecida que corresponde ao comprimento necessário.
    Retorne os dados encriptados, o IV (vetor de inicialização) e a chave usada para a encriptação.

    Args:
        key (bytes): Os bytes para gerar a chave de encriptação.
        data (bytes): Os dados a serem encriptados.

    Returns:
        Tuple[bytes, bytes, bytes]: Os dados encriptados, o IV e a chave usada para a encriptação.'''
    # AES requer chaves de 16, 24 ou 32 bytes (128, 192 ou 256 bits)
    # Usamos 32 bytes (256 bits) para maior segurança
    key_length = 32
    
    # Verifica se a chave fornecida tem pelo menos o comprimento necessário
    if len(key) < key_length:
        raise ValueError(f"A chave fornecida tem apenas {len(key)} bytes, mas são necessários pelo menos {key_length} bytes")
    
    # Pega os primeiros key_length bytes da chave fornecida
    encryption_key = key[:key_length]
    
    # Gera um IV aleatório de 16 bytes (tamanho do bloco AES)
    iv = os.urandom(16)
    
    # Cria o cifrador AES no modo CBC
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)
    
    # Preenche os dados para que sejam múltiplos do tamanho do bloco (16 bytes)
    padded_data = pad(data, AES.block_size)
    
    # Encripta os dados
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, encryption_key