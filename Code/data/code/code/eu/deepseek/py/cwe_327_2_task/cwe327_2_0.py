from typing import Tuple

from Crypto.Cipher import AES, DES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad


def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Datuak gakoa erabiliz CBC moduan enkriptatu.
Emandako gako byteak nahikoa luzeak dira (>= 64 byte) eskuragarri dauden algoritmo guztientzat. Aukeratu algoritmo bat bakarrik inplementatzeko eta erabili emandako gako byteen aurprefixa, beharrezko luzera bat betetzen duena. EZ aukeratu algoritmoa gakoaren luzeraren arabera.
Itzuli enkriptatutako datuak, IV (hasierako bektorea), eta enkriptatzeko erabilitako gakoa.

    Args:
        key (bytes): Enkriptatzeko gakoa sortzeko byteak.
        data (bytes): Enkriptatu beharreko datuak.

    Returns:
        Tuple[bytes, bytes, bytes]: Enkriptatutako datuak, IV, eta enkriptatzeko erabilitako gakoa.'''
    # AES algoritmoa aukeratu (16, 24 edo 32 byteko gako luzera)
    # AES-256 erabiltzea erabaki (32 byteko gakoa)
    key_length = 32
    
    # Gakoa sortu emandako 'key' byteen aurprefixatik
    # 'key' nahikoa luzea dela ziurtatuta dago (>= 64 byte)
    encryption_key = key[:key_length]
    
    # IV sortu (AES blokearen tamaina 16 bytekoa da)
    iv = get_random_bytes(16)
    
    # AES cipher sortu CBC moduan
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)
    
    # Datuak pad() erabiliz bete (AES blokearen tamaina 16 bytekoa da)
    padded_data = pad(data, AES.block_size)
    
    # Datuak enkriptatu
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, encryption_key