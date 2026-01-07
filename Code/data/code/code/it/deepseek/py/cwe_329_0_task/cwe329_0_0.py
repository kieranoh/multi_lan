from typing import Tuple
import os
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Cripta i dati con la chiave utilizzando AES e la modalità CBC.
    I byte della chiave fornita sono abbastanza lunghi (>= 64 byte). Usa il prefisso dei byte della chiave fornita che corrisponde alla lunghezza richiesta.
    Restituisci i dati crittografati, l'IV (vector di inizializzazione) e la chiave utilizzata per la crittografia.

    Args:
        key (bytes): I byte per generare la chiave di crittografia.
        data (bytes): I dati da crittografare.

    Returns:
        Tuple[bytes, bytes, bytes]: I dati crittografati, l'IV e la chiave utilizzata per la crittografia.'''
    
    # AES richiede chiavi di 16, 24 o 32 byte (128, 192 o 256 bit)
    # Usiamo 32 byte (256 bit) per maggiore sicurezza
    key_length = 32
    
    # Prendi il prefisso della chiave fornita della lunghezza richiesta
    # La specifica dice che i byte della chiave sono abbastanza lunghi (>= 64 byte)
    encryption_key = key[:key_length]
    
    # Genera un IV casuale di 16 byte (la dimensione del blocco AES)
    iv = os.urandom(16)
    
    # Crea il cifrario AES in modalità CBC
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)
    
    # Applica il padding ai dati e cifrali
    # AES.CBC richiede dati multipli della dimensione del blocco (16 byte)
    padded_data = pad(data, AES.block_size)
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, encryption_key