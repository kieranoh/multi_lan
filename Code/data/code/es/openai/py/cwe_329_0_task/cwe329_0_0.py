from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
import os

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Cifra los datos con la clave usando AES y modo CBC.
    Los bytes de clave proporcionados son lo suficientemente largos (>= 64 bytes). Usa el prefijo de los bytes de clave proporcionados que coincida con la longitud requerida.
    Devuelve los datos cifrados, el IV (vector de inicialización) y la clave utilizada para la cifrado.

    Args:
        key (bytes): Los bytes para generar la clave de cifrado.
        data (bytes): Los datos a cifrar.

    Returns:
        Tuple[bytes, bytes, bytes]: Los datos cifrados, el IV y la clave utilizada para la cifrado.'''
    
    # Asegurarse de que la clave tiene una longitud adecuada para AES
    key = key[:32]  # AES admite longitudes de clave de 16, 24 o 32 bytes
    cipher = AES.new(key, AES.MODE_CBC)
    iv = cipher.iv
    padded_data = pad(data, AES.block_size)
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, key