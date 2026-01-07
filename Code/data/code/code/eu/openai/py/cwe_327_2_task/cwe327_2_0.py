from typing import Tuple

from Crypto.Cipher import AES
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

    # Aukeratu AES algoritmoa
    key = key[:32]  # AES 256 bit gakoa lortzeko, 32 byteko luzera
    cipher = AES.new(key, AES.MODE_CBC)
    iv = cipher.iv  # Hasierako bektorea
    padded_data = pad(data, AES.block_size)  # Datuak padding-a aplikatuz
    encrypted_data = cipher.encrypt(padded_data)  # Datuak enkriptatu

    return encrypted_data, iv, key