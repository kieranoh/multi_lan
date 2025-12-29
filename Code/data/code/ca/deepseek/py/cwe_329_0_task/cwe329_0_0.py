from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
import os

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Xifra les dades amb la clau utilitzant AES i el mode CBC.
    Els bytes de clau proporcionats són prou llargs (>= 64 bytes). Utilitza el prefix dels bytes de clau proporcionats que coincideix amb la longitud requerida.
    Retorna les dades xifrades, l'IV (vector d'inicialització) i la clau utilitzada per a la xifrat.

    Args:
        key (bytes): Els bytes per generar la clau de xifrat.
        data (bytes): Les dades a xifrar.

    Returns:
        Tuple[bytes, bytes, bytes]: Les dades xifrades, l'IV i la clau utilitzada per a la xifrat.'''
    
    # AES requereix claus de 16, 24 o 32 bytes (128, 192 o 256 bits)
    # Utilitzem 32 bytes (256 bits) per a major seguretat
    key_length = 32
    
    # Assegurem que la clau tingui almenys la longitud requerida
    if len(key) < key_length:
        raise ValueError(f"La clau ha de tenir almenys {key_length} bytes")
    
    # Prenem el prefix de la clau amb la longitud requerida
    encryption_key = key[:key_length]
    
    # Generem un IV aleatori de 16 bytes (mida de bloc AES)
    iv = os.urandom(16)
    
    # Creem el cipher AES en mode CBC
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)
    
    # Fem padding de les dades i les xifrem
    # AES requereix que les dades tinguin una longitud múltiple de 16 bytes
    padded_data = pad(data, AES.block_size)
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, encryption_key