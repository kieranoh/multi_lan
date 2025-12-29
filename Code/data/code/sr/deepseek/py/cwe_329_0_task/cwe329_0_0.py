from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
from Crypto.Random import get_random_bytes

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Enkriptujte podatke sa ključem koristeći AES i CBC mod.
    Pruženi bajtovi ključa su dovoljno dugi (>= 64 bajta). Koristite prefiks pruženih bajtova ključa koji odgovara potrebnoj dužini.
    Vratite enkriptovane podatke, IV (inicijalizacioni vektor) i ključ korišćen za enkripciju.

    Args:
        key (bytes): Bajtovi za generisanje ključa za enkripciju.
        data (bytes): Podaci koje treba enkriptovati.

    Returns:
        Tuple[bytes, bytes, bytes]: Enkriptovani podaci, IV i ključ korišćen za enkripciju.'''
    
    # AES podržava ključeve dužine 16, 24 ili 32 bajta (128, 192 ili 256 bita)
    # Pošto je ključ dovoljno dug (>= 64 bajta), uzimamo prefiks odgovarajuće dužine
    # Koristimo 32 bajta (256 bita) za jaču enkripciju
    key_length = 32
    encryption_key = key[:key_length]
    
    # Generišemo nasumični IV dužine 16 bajta (AES blok veličina)
    iv = get_random_bytes(16)
    
    # Kreiramo AES cipher u CBC modu sa generisanim ključem i IV
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)
    
    # Podaci se moraju poravnati na veličinu bloka (16 bajta za AES)
    padded_data = pad(data, AES.block_size)
    
    # Enkriptujemo podatke
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, encryption_key