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

    # Utilitzar els primers 16 bytes de la clau donada per AES-128
    aes_key = key[:16]
    
    # Generar un IV aleatori
    iv = os.urandom(AES.block_size)
    
    # Crear el cipher
    cipher = AES.new(aes_key, AES.MODE_CBC, iv)
    
    # Xifrar les dades
    encrypted_data = cipher.encrypt(pad(data, AES.block_size))
    
    return encrypted_data, iv, aes_key