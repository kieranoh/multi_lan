from typing import Tuple
from Crypto.Cipher import AES, DES
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
    
    # Scelgo AES-256 come algoritmo (scelta fissa, non basata sulla lunghezza della chiave)
    # AES-256 richiede una chiave di 32 byte (256 bit)
    KEY_LENGTH = 32
    BLOCK_SIZE = AES.block_size
    
    # Prendo i primi KEY_LENGTH byte della chiave fornita
    encryption_key = key[:KEY_LENGTH]
    
    # Genera un IV casuale della dimensione del blocco AES (16 byte)
    iv = get_random_bytes(BLOCK_SIZE)
    
    # Crea il cifrario AES in modalità CBC
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)
    
    # Applica il padding ai dati e crittografa
    padded_data = pad(data, BLOCK_SIZE)
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, encryption_key