from typing import Tuple
import os

from Crypto.Cipher import AES
from Crypto.Util.Padding import pad


def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Kryptera datan med nyckeln med hjälp av AES och CBC-läge.
    De angivna nyckelbytes är tillräckligt långa (>= 64 bytes). Använd prefixet av de angivna nyckelbytes som matchar den erforderliga längden.
    Returnera den krypterade datan, IV (initialiseringsvektor) och nyckeln som användes för kryptering.

    Args:
        key (bytes): Bytesen för att generera krypteringsnyckeln.
        data (bytes): Datan som ska krypteras.

    Returns:
        Tuple[bytes, bytes, bytes]: Den krypterade datan, IV och nyckeln som användes för kryptering.'''
    # AES-256 kräver 32 bytes nyckel
    aes_key_length = 32
    # Använd prefixet av de angivna nyckelbytes som matchar den erforderliga längden
    encryption_key = key[:aes_key_length]
    
    # Generera en slumpmässig IV på 16 bytes (AES blockstorlek)
    iv = os.urandom(16)
    
    # Skapa AES cipher i CBC-läge med den givna nyckeln och IV
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)
    
    # Pad data till AES blockstorlek och kryptera
    padded_data = pad(data, AES.block_size)
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, encryption_key