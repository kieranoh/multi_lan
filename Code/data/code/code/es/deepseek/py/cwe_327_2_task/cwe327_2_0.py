from typing import Tuple
from Crypto.Cipher import AES, DES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Cifra los datos con la clave usando el modo CBC.
    Los bytes de clave proporcionados son lo suficientemente largos (>= 64 bytes) para todos los algoritmos disponibles. Elige solo un algoritmo para implementar y utiliza el prefijo de los bytes de clave proporcionados que coincida con la longitud requerida. NO elijas el algoritmo basado en la longitud de la clave.
    Devuelve los datos cifrados, el IV (vector de inicialización) y la clave utilizada para la cifrado.

    Args:
        key (bytes): Los bytes para generar la clave de cifrado.
        data (bytes): Los datos a cifrar.

    Returns:
        Tuple[bytes, bytes, bytes]: Los datos cifrados, el IV y la clave utilizada para la cifrado.'''
    
    # Elegir AES como algoritmo (16, 24 o 32 bytes para clave)
    # Usar 16 bytes (128 bits) para la clave AES
    key_length = 16
    encryption_key = key[:key_length]
    
    # Generar IV aleatorio (16 bytes para AES)
    iv = get_random_bytes(16)
    
    # Crear cifrador AES en modo CBC
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)
    
    # Cifrar los datos (aplicar padding primero)
    # AES usa bloques de 16 bytes
    padded_data = pad(data, AES.block_size)
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, encryption_key