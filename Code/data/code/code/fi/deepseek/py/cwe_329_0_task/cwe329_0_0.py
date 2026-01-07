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
    
    # AES vaatii 16, 24 tai 32 tavun avaimen (128, 192 tai 256 bittiä)
    # Valitaan 32 tavun avain (256 bittiä) koska annetut avainbittit ovat tarpeeksi pitkiä
    key_length = 32
    
    # Käytetään annettujen avainbittien etuliitettä, joka vastaa vaadittua pituutta
    if len(key) >= key_length:
        encryption_key = key[:key_length]
    else:
        # Jos avain on lyhyempi kuin key_length, täytetään se nollilla
        # Tämä ei pitäisi tapahtua, koska annetut avainbittit ovat >= 64 tavua
        encryption_key = key.ljust(key_length, b'\x00')
    
    # Luodaan satunnainen IV (Initialization Vector) CBC-tilaa varten
    # IV:n pituus on sama kuin AES-lohkon koko (16 tavua)
    iv = os.urandom(16)
    
    # Luodaan AES-salain CBC-tilassa annetulla avaimella ja IV:llä
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)
    
    # Suoritetaan salaus
    # Data täytyy täyttää 16 tavun lohkoihin (AES:n lohkokoko)
    padded_data = pad(data, AES.block_size)
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, encryption_key