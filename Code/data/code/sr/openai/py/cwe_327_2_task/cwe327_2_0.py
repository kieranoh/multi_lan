from typing import Tuple

from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Enkriptujte podatke sa ključem koristeći CBC mod.    Pruženi bajtovi ključa su dovoljno dugi (>= 64 bajta) za sve dostupne algoritme. Izaberite samo jedan algoritam za implementaciju i koristite prefiks pruženih bajtova ključa koji odgovara potrebnoj dužini. NE birajte algoritam na osnovu dužine ključa.    Vratite enkriptovane podatke, IV (inicijalizacioni vektor) i ključ korišćen za enkripciju.    Args:        key (bytes): Bajtovi za generisanje ključa za enkripciju.        data (bytes): Podaci koje treba enkriptovati.    Returns:        Tuple[bytes, bytes, bytes]: Enkriptovani podaci, IV i ključ koji se koristi za enkripciju.'''
    
    # Uzimamo prvih 16 bajtova ključa za AES
    aes_key = key[:16]
    
    # Generišemo inicijalizacioni vektor
    iv = get_random_bytes(16)
    
    # Kreiramo AES cifar sa CBC modom
    cipher = AES.new(aes_key, AES.MODE_CBC, iv)
    
    # Enkriptujemo podatke
    encrypted_data = cipher.encrypt(pad(data, AES.block_size))
    
    return encrypted_data, iv, aes_key