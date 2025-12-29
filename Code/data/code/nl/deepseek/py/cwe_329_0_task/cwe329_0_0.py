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
    # AES-256 vereist een sleutel van 32 bytes (256 bits)
    aes_key_length = 32
    # Neem de eerste 32 bytes van de opgegeven sleutel als AES-sleutel
    aes_key = key[:aes_key_length]
    
    # Genereer een willekeurige IV van 16 bytes (AES blokgrootte)
    iv = os.urandom(16)
    
    # Maak een AES-cipher object in CBC-modus met de sleutel en IV
    cipher = AES.new(aes_key, AES.MODE_CBC, iv)
    
    # Versleutel de gegevens (pad eerst naar AES blokgrootte)
    encrypted_data = cipher.encrypt(pad(data, AES.block_size))
    
    return encrypted_data, iv, aes_key