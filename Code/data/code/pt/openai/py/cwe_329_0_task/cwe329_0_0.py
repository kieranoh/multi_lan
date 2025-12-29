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
    
    # Use os primeiros 16 bytes da chave para a cifra AES
    aes_key = key[:16]
    
    # Criar um vetor de inicialização (IV) aleatório
    iv = os.urandom(AES.block_size)
    
    # Configurar o cipher AES em modo CBC
    cipher = AES.new(aes_key, AES.MODE_CBC, iv)
    
    # Padronizar os dados e encriptá-los
    encrypted_data = cipher.encrypt(pad(data, AES.block_size))
    
    return encrypted_data, iv, aes_key