from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Crittografa i dati con la chiave utilizzando la modalità CBC.
    La chiave fornita è abbastanza lunga (>= 64 byte) per tutti gli algoritmi disponibili. Scegli solo un algoritmo da implementare e utilizza il prefisso dei byte della chiave fornita che corrisponde alla lunghezza richiesta. NON scegliere l'algoritmo in base alla lunghezza della chiave.
    Restituisci i dati crittografati, l'IV (vector di inizializzazione) e la chiave utilizzata per la crittografia.

    Args:
        key (bytes): I byte per generare la chiave di crittografia.
        data (bytes): I dati da crittografare.

    Returns:
        Tuple[bytes, bytes, bytes]: I dati crittografati, l'IV e la chiave utilizzata per la crittografia.'''
    
    # Definire la lunghezza della chiave per AES
    key_length = 16  # 128 bit
    aes_key = key[:key_length]
    
    # Creare un IV casuale
    iv = get_random_bytes(AES.block_size)
    
    # Creare un cipher AES in modalità CBC
    cipher = AES.new(aes_key, AES.MODE_CBC, iv)
    
    # Crittografare i dati
    encrypted_data = cipher.encrypt(pad(data, AES.block_size))
    
    return encrypted_data, iv, aes_key