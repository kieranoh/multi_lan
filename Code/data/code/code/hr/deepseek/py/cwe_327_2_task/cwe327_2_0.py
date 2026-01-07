from typing import Tuple
from Crypto.Cipher import AES, DES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Šifrirajte podatke s ključem koristeći CBC način. Pruženi bajtovi ključa su dovoljno dugi (>= 64 bajta) za sve dostupne algoritme. Odaberite samo jedan algoritam za implementaciju i koristite prefiks pruženih bajtova ključa koji odgovara potrebnoj duljini. NE birajte algoritam na temelju duljine ključa. Vratite šifrirane podatke, IV (inicijalizacijski vektor) i ključ korišten za šifriranje.

    Args:
        key (bytes): Bajtovi za generiranje ključa za šifriranje.
        data (bytes): Podaci za šifriranje.

    Returns:
        Tuple[bytes, bytes, bytes]: Šifrirani podaci, IV i ključ korišten za šifriranje.'''
    # Odabir AES algoritma (fiksni izbor prema specifikaciji)
    # AES podržava ključeve duljine 16, 24 ili 32 bajta
    # Koristimo AES-256 (32 bajta) jer je najsigurniji od dostupnih opcija
    key_length = 32  # 256-bitni ključ za AES
    
    # Uzimamo prefiks pruženog ključa potrebne duljine
    encryption_key = key[:key_length]
    
    # Generiramo IV (inicijalizacijski vektor) odgovarajuće duljine za AES-CBC
    # AES blok je 16 bajta, pa IV mora biti iste duljine
    iv = get_random_bytes(16)
    
    # Kreiramo AES cipher u CBC načinu rada
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)
    
    # Podaci se moraju poravnati na veličinu bloka AES-a (16 bajta)
    padded_data = pad(data, AES.block_size)
    
    # Šifriramo podatke
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, encryption_key