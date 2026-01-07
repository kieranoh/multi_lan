from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
import os

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Salaa tiedot avaimella käyttäen AES:ää ja CBC-tilaa.
    Annetut avainbittit ovat tarpeeksi pitkiä (>= 64 tavua). Käytä annettujen avainbittien etuliitettä, joka vastaa vaadittua pituutta.
    Palauta salatut tiedot, IV (alkuvectori) ja avain, jota käytettiin salaamiseen.

    Args:
        key (bytes): Tavut, joista luodaan salausavain.
        data (bytes): Salattavat tiedot.

    Returns:
        Tuple[bytes, bytes, bytes]: Salatut tiedot, IV ja avain, jota käytettiin salaamiseen.'''
    
    # Luo aloitusvektori (IV)
    iv = os.urandom(AES.block_size)
    
    # Luo AES-salausobjekti CBC-tilassa
    cipher = AES.new(key, AES.MODE_CBC, iv)
    
    # Täydennä tiedot ja salaa ne
    encrypted_data = cipher.encrypt(pad(data, AES.block_size))
    
    return encrypted_data, iv, key