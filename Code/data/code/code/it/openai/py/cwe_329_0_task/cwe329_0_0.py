from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
import os

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Cripta i dati con la chiave utilizzando AES e la modalità CBC.
    I byte della chiave fornita sono abbastanza lunghi (>= 64 byte). Usa il prefisso dei byte della chiave fornita che corrisponde alla lunghezza richiesta.
    Restituisci i dati crittografati, l'IV (vector di inizializzazione) e la chiave utilizzata per la crittografia.

    Args:
        key (bytes): I byte per generare la chiave di crittografia.
        data (bytes): I dati da crittografare.

    Returns:
        Tuple[bytes, bytes, bytes]: I dati crittografati, l'IV e la chiave utilizzata per la crittografia.'''
    
    # AES richiede una chiave di 16, 24 o 32 byte
    key_length = 32  # Utilizziamo una chiave di 32 byte (256 bit)
    effective_key = key[:key_length]  # Truncare la chiave se è più lunga

    # Creazione di un IV casuale per la modalità CBC
    iv = os.urandom(AES.block_size)

    # Inizializzazione del cifrario AES in modalità CBC
    cipher = AES.new(effective_key, AES.MODE_CBC, iv)

    # Padding dei dati per renderli un multiplo della dimensione del blocco
    padded_data = pad(data, AES.block_size)

    # Crittografia dei dati
    encrypted_data = cipher.encrypt(padded_data)

    return encrypted_data, iv, effective_key