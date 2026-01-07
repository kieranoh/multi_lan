from typing import Tuple
from Crypto.Cipher import AES, DES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Enkriptujte podatke sa ključem koristeći CBC mod.
    Pruženi bajtovi ključa su dovoljno dugi (>= 64 bajta) za sve dostupne algoritme.
    Izaberite samo jedan algoritam za implementaciju i koristite prefiks pruženih bajtova
    ključa koji odgovara potrebnoj dužini. NE birajte algoritam na osnovu dužine ključa.
    
    Vratite enkriptovane podatke, IV (inicijalizacioni vektor) i ključ korišćen za enkripciju.
    
    Args:
        key (bytes): Bajtovi za generisanje ključa za enkripciju.
        data (bytes): Podaci koje treba enkriptovati.
    
    Returns:
        Tuple[bytes, bytes, bytes]: Enkriptovani podaci, IV i ključ korišćen za enkripciju.
    '''
    # Odlučujem se za AES-256 algoritam (256 bita = 32 bajta)
    # Pošto specifikacija kaže da ne biram algoritam na osnovu dužine ključa,
    # fiksiram izbor na AES-256
    key_length = 32  # 32 bajta = 256 bita za AES-256
    
    # Uzimamo prefiks ključa odgovarajuće dužine
    encryption_key = key[:key_length]
    
    # Generišemo IV odgovarajuće dužine za AES (16 bajta za AES blok)
    iv = get_random_bytes(16)
    
    # Kreiramo AES cipher u CBC modu
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)
    
    # Padd-ujemo podatke pre enkripcije (AES blok veličina je 16 bajta)
    padded_data = pad(data, AES.block_size)
    
    # Enkriptujemo podatke
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, encryption_key