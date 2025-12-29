from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
from Crypto.Random import get_random_bytes

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Cifra los datos con la clave usando AES y modo CBC.
    Los bytes de clave proporcionados son lo suficientemente largos (>= 64 bytes). Usa el prefijo de los bytes de clave proporcionados que coincida con la longitud requerida.
    Devuelve los datos cifrados, el IV (vector de inicialización) y la clave utilizada para la cifrado.

    Args:
        key (bytes): Los bytes para generar la clave de cifrado.
        data (bytes): Los datos a cifrar.

    Returns:
        Tuple[bytes, bytes, bytes]: Los datos cifrados, el IV y la clave utilizada para la cifrado.'''
    # AES requiere claves de 16, 24 o 32 bytes (128, 192 o 256 bits)
    # Usamos 32 bytes (256 bits) para máxima seguridad
    key_length = 32
    
    # Tomamos el prefijo de la clave proporcionada según la longitud requerida
    # La documentación indica que los bytes de clave son >= 64 bytes, así que hay suficientes
    encryption_key = key[:key_length]
    
    # Generamos un IV aleatorio de 16 bytes (tamaño de bloque AES)
    iv = get_random_bytes(16)
    
    # Creamos el cifrador AES en modo CBC
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)
    
    # Aplicamos padding a los datos y los ciframos
    padded_data = pad(data, AES.block_size)
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, encryption_key