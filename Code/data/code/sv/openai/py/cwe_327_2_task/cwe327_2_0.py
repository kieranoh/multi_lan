from typing import Tuple
from Crypto.Cipher import AES
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
    
    # Definiera AES-nyckelns längd
    aes_key_length = 16  # Använd 16 bytes för AES-128
    aes_key = key[:aes_key_length]  # Ta de första 16 bytes av nyckeln

    # Skapa en initieringsvektor (IV)
    iv = get_random_bytes(AES.block_size)

    # Skapa en cypher med AES i CBC-läge
    cipher = AES.new(aes_key, AES.MODE_CBC, iv)

    # Pad datan och kryptera
    padded_data = pad(data, AES.block_size)
    encrypted_data = cipher.encrypt(padded_data)

    return encrypted_data, iv, aes_key