from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
import os

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Enkriptirajte podatke s ključem koristeći AES i CBC način.
    Pruženi bajtovi ključa su dovoljno dugi (>= 64 bajta). Koristite prefiks pruženih bajtova ključa koji odgovara potrebnoj duljini.
    Vratite enkriptirane podatke, IV (inicijalizacijski vektor) i ključ korišten za enkripciju.
    Args:
        key (bytes): Bajtovi za generiranje ključa za enkripciju.
        data (bytes): Podaci za enkripciju.
    Returns:
        Tuple[bytes, bytes, bytes]: Enkriptirani podaci, IV i ključ korišten za enkripciju.
    '''
    # AES-256 zahtijeva 32-bajtni ključ (256 bita)
    aes_key_length = 32
    
    # Uzmemo prefiks ključa odgovarajuće duljine
    # Funkcija će raditi i ako je ključ točno 32 bajta, ali specifikacija kaže >= 64 bajta
    encryption_key = key[:aes_key_length]
    
    # Generiraj nasumični IV (16 bajta za AES blok)
    iv = os.urandom(16)
    
    # Stvori AES cipher objekt u CBC načinu rada
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)
    
    # Podaci se moraju poravnati na veličinu bloka AES-a (16 bajta)
    padded_data = pad(data, AES.block_size)
    
    # Enkriptiraj podatke
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, encryption_key