from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
import os

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Kryptera datan med nyckeln med hjälp av AES och CBC-läge.
    De angivna nyckelbytes är tillräckligt långa (>= 64 bytes). Använd prefixet av de angivna nyckelbytes som matchar den erforderliga längden.
    Returnera den krypterade datan, IV (initialiseringsvektor) och nyckeln som användes för kryptering.

    Args:
        key (bytes): Bytesen för att generera krypteringsnyckeln.
        data (bytes): Datan som ska krypteras.

    Returns:
        Tuple[bytes, bytes, bytes]: Den krypterade datan, IV och nyckeln som användes för kryptering.'''
    
    # Skapa en AES-nyckel med en längd av 16, 24 eller 32 bytes
    aes_key = key[:32]  # Tar de första 32 bytes av den angivna nyckeln om den är längre
    
    # Skapa en initialiseringsvektor (IV)
    iv = os.urandom(AES.block_size)  # AES.block_size är 16 bytes
    
    # Skapa en AES-krypterare i CBC-läge
    cipher = AES.new(aes_key, AES.MODE_CBC, iv)
    
    # Padda datan så att den är en multipel av blockstorleken
    padded_data = pad(data, AES.block_size)
    
    # Kryptera datan
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, aes_key