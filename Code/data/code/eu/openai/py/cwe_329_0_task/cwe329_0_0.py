from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
import os

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Datuak AES eta CBC moduan gakoa erabiliz enkriptatu.
Emandako gako byteak nahikoa luzeak dira (>= 64 byte). Erabili emandako gako byteen aurprefikua behar den luzera egokitzen dena.
Itzuli enkriptatutako datuak, IV (hasierako bideratzailea) eta enkriptatzeko erabilitako gakoa.

    Args:
        key (bytes): Enkriptatzeko gakoa sortzeko byteak.
        data (bytes): Enkriptatu beharreko datuak.

    Returns:
        Tuple[bytes, bytes, bytes]: Enkriptatutako datuak, IV, eta enkriptatzeko erabilitako gakoa.'''
    
    # Gakoa 16, 24 edo 32 byte luzera egokitu
    key = key[:32]  # Max 32 byte AES gakoaren luzera
    iv = os.urandom(AES.block_size)  # Hasierako bideratzailea sortu
    cipher = AES.new(key, AES.MODE_CBC, iv)  # AES enkriptatzailea sortu
    encrypted_data = cipher.encrypt(pad(data, AES.block_size))  # Datuak enkriptatu

    return encrypted_data, iv, key