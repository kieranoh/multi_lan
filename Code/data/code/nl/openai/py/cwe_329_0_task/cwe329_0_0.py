from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
import os

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Versleutel de gegevens met de sleutel met behulp van AES en CBC-modus.
    De opgegeven sleutelbytes zijn lang genoeg (>= 64 bytes). Gebruik het voorvoegsel van de opgegeven sleutelbytes dat overeenkomt met de vereiste lengte.
    Geef de versleutelde gegevens, de IV (initialisatievector) en de sleutel die voor versleuteling is gebruikt terug.

    Args:
        key (bytes): De bytes om de versleutelingssleutel te genereren.
        data (bytes): De te versleutelen gegevens.

    Returns:
        Tuple[bytes, bytes, bytes]: De versleutelde gegevens, de IV en de sleutel die voor versleuteling is gebruikt.'''
    
    # AES vereist een sleutel van 16, 24 of 32 bytes
    # We gebruiken de eerste 32 bytes van de gegeven sleutel
    aes_key = key[:32]
    
    # Initialize de cipher in CBC modus met een random IV
    cipher = AES.new(aes_key, AES.MODE_CBC)
    iv = cipher.iv
    
    # Pad de gegevens en versleutel ze
    padded_data = pad(data, AES.block_size)
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, aes_key