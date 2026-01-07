from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
import os

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Zašifrujte data s klíčem pomocí AES a režimu CBC.
    Poskytnuté bajty klíče jsou dostatečně dlouhé (>= 64 bajtů). Použijte prefix poskytnutých bajtů klíče, který odpovídá požadované délce.
    Vraťte zašifrovaná data, IV (inicializační vektor) a klíč použitý pro šifrování.

    Args:
        key (bytes): Bajty pro generování šifrovacího klíče.
        data (bytes): Data k zašifrování.

    Returns:
        Tuple[bytes, bytes, bytes]: Zašifrovaná data, IV a klíč použitý pro šifrování.'''
    
    # AES vyžaduje klíč o délce 16, 24 nebo 32 bajtů
    key_length = 32  # Vybereme 32 bajtů pro AES-256
    aes_key = key[:key_length]

    # Inicializační vektor (IV) pro CBC
    iv = os.urandom(AES.block_size)

    # Vytvoření šifrovacího objektu
    cipher = AES.new(aes_key, AES.MODE_CBC, iv)

    # Zašifrování dat
    encrypted_data = cipher.encrypt(pad(data, AES.block_size))

    return encrypted_data, iv, aes_key