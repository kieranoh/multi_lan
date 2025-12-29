from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
import os

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Enkriptujte podatke sa ključem koristeći AES i CBC mod.
    Pruženi bajtovi ključa su dovoljno dugi (>= 64 bajta). Koristite prefiks pruženih bajtova ključa koji odgovara potrebnoj dužini.
    Vratite enkriptovane podatke, IV (inicijalizacioni vektor) i ključ korišćen za enkripciju.

    Args:
        key (bytes): Bajtovi za generisanje ključa za enkripciju.
        data (bytes): Podaci koje treba enkriptovati.

    Returns:
        Tuple[bytes, bytes, bytes]: Enkriptovani podaci, IV i ključ korišćen za enkripciju.'''
    
    # Izaberite potrebnu dužinu ključa za AES (npr. 16, 24 ili 32 bajta)
    key_length = 32  # Koristimo 256-bitni ključ
    aes_key = key[:key_length]
    
    # Inicijalizacija vektora (IV)
    iv = os.urandom(AES.block_size)
    
    # Kreiranje AES cifratora
    cipher = AES.new(aes_key, AES.MODE_CBC, iv)
    
    # Padovanje podataka i enkripcija
    encrypted_data = cipher.encrypt(pad(data, AES.block_size))
    
    return encrypted_data, iv, aes_key