from typing import Tuple

from Crypto.Cipher import AES
from Crypto.Util.Padding import pad


def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Datuak AES eta CBC moduan gakoa erabiliz enkriptatu.
Emandako gako byteak nahikoa luzeak dira (>= 64 byte). Erabili emandako gako byteen aurprefikua behar den luzera egokitzen dena.
Itzuli enkriptatutako datuak, IV (hasierako bideratzailea) eta enkriptatzeko erabilitako gakoa.

    Args:
        key (bytes): Enkriptatzeko gakoa sortzeko byteak.
        data (bytes): Enkriptatu beharreko datuak.

    Returns:
        Tuple[bytes, bytes, bytes]: Enkriptatutako datuak, IV, eta enkriptatzeko erabilitako gakoa.'''
    # AES-256 erabiltzeko 32 byteko gakoa behar da (256 bit)
    aes_key_length = 32
    
    # Erabili emandako gakoaren aurprefikoa behar den luzerarako
    # Gakoa nahikoa luzea dela ziurtatuta dago (>= 64 byte), beraz slice segurua da
    encryption_key = key[:aes_key_length]
    
    # Sortu AES cipher CBC moduan
    cipher = AES.new(encryption_key, AES.MODE_CBC)
    
    # Datuak pad() erabiliz bete AES bloke tamainara (16 byte)
    padded_data = pad(data, AES.block_size)
    
    # Datuak enkriptatu
    encrypted_data = cipher.encrypt(padded_data)
    
    # Itzuli enkriptatutako datuak, IV, eta erabilitako gakoa
    return encrypted_data, cipher.iv, encryption_key