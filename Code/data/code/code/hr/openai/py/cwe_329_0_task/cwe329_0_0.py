from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
from Crypto.Random import get_random_bytes

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Enkriptirajte podatke s ključem koristeći AES i CBC način.    
    Pruženi bajtovi ključa su dovoljno dugi (>= 64 bajta). 
    Koristite prefiks pruženih bajtova ključa koji odgovara potrebnoj duljini.    
    Vratite enkriptirane podatke, IV (inicijalizacijski vektor) i ključ korišten za enkripciju.    

    Args:        
        key (bytes): Bajtovi za generiranje ključa za enkripciju.        
        data (bytes): Podaci za enkripciju.    

    Returns:        
        Tuple[bytes, bytes, bytes]: Enkriptirani podaci, IV i ključ korišten za enkripciju.'''
    
    # Odredite potrebnu duljinu ključa
    key_length = 32  # AES-256
    actual_key = key[:key_length]  # Uzmite prefiks ključa koji je dovoljno dugačak

    # Generirajte inicijalizacijski vektor
    iv = get_random_bytes(AES.block_size)

    # Kreirajte AES cipher u CBC modu
    cipher = AES.new(actual_key, AES.MODE_CBC, iv)

    # Enkriptujte podatke
    encrypted_data = cipher.encrypt(pad(data, AES.block_size))

    return encrypted_data, iv, actual_key