from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Šifrirajte podatke s ključem koristeći CBC način. Pruženi bajtovi ključa su dovoljno dugi (>= 64 bajta) za sve dostupne algoritme. Odaberite samo jedan algoritam za implementaciju i koristite prefiks pruženih bajtova ključa koji odgovara potrebnoj duljini. NE birajte algoritam na temelju duljine ključa. Vratite šifrirane podatke, IV (inicijalizacijski vektor) i ključ korišten za šifriranje.

    Args:
        key (bytes): Bajtovi za generiranje ključa za šifriranje.
        data (bytes): Podaci za šifriranje.

    Returns:
        Tuple[bytes, bytes, bytes]: Šifrirani podaci, IV i ključ korišten za šifriranje.'''
    
    # Određivanje duljine ključa za AES (16, 24 ili 32 bajta)
    aes_key = key[:32]  # Koristimo prvih 32 bajta za AES
    cipher = AES.new(aes_key, AES.MODE_CBC)
    
    # Generiranje inicijalizacijskog vektora
    iv = cipher.iv
    
    # Dodavanje popunjjavanja podacima
    padded_data = pad(data, AES.block_size)
    
    # Šifriranje podataka
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, aes_key