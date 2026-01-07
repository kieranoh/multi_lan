from typing import Tuple
import os

from Crypto.Cipher import AES
from Crypto.Util.Padding import pad


def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Zašifrujte data s klíčem pomocí AES a režimu CBC.
    Poskytnuté bajty klíče jsou dostatečně dlouhé (>= 64 bajtů). Použijte prefix poskytnutých bajtů klíče, který odpovídá požadované délce.
    Vraťte zašifrovaná data, IV (inicializační vektor) a klíč použitý pro šifrování.

    Args:
        key (bytes): Bajty pro generování šifrovacího klíče.
        data (bytes): Data k zašifrování.

    Returns:
        Tuple[bytes, bytes, bytes]: Zašifrovaná data, IV a klíč použitý pro šifrování.'''
    # AES-256 vyžaduje 32-bajtový klíč (256 bitů)
    aes_key_length = 32
    # Zajistíme, že použijeme pouze prefix klíče o požadované délce
    encryption_key = key[:aes_key_length]
    
    # Vygenerujeme náhodný IV (16 bajtů pro AES)
    iv = os.urandom(16)
    
    # Vytvoříme šifrovací objekt AES v režimu CBC
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)
    
    # Data musí být zarovnána na velikost bloku AES (16 bajtů)
    padded_data = pad(data, AES.block_size)
    
    # Zašifrujeme data
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, encryption_key