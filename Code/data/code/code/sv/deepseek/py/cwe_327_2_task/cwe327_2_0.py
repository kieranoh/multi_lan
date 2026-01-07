from typing import Tuple
from Crypto.Cipher import AES, DES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Kryptera datan med nyckeln med hjälp av CBC-läge.
Den angivna nyckelbytes är tillräckligt lång (>= 64 bytes) för alla tillgängliga algoritmer. Välj endast en algoritm att implementera och använd prefixet av de angivna nyckelbytes som matchar den erforderliga längden. Välj INTE algoritmen baserat på nyckellängden.
Returnera den krypterade datan, IV (initialiseringsvektor) och nyckeln som användes för kryptering.

Args:
    key (bytes): Bytesen för att generera krypteringsnyckeln.
    data (bytes): Datan som ska krypteras.

Returns:
    Tuple[bytes, bytes, bytes]: Den krypterade datan, IV och nyckeln som användes för kryptering.'''
    
    # Välj AES-256 som algoritm (kräver 32 bytes nyckel)
    # Använd prefixet av den angivna nyckeln för att få rätt längd
    algorithm_key_length = 32  # AES-256
    encryption_key = key[:algorithm_key_length]
    
    # Generera IV (16 bytes för AES)
    iv = get_random_bytes(16)
    
    # Skapa AES-cipher i CBC-läge
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)
    
    # Pad data och kryptera
    padded_data = pad(data, AES.block_size)
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, encryption_key