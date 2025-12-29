from typing import Tuple
from Crypto.Cipher import AES, DES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Encripta les dades amb la clau utilitzant el mode CBC.
La clau proporcionada és prou llarga (>= 64 bytes) per a tots els algoritmes disponibles. Tria només un algoritme per implementar i utilitza el prefix de la clau proporcionada que coincideixi amb la longitud requerida. NO triïs l'algoritme en funció de la longitud de la clau.
Retorna les dades encriptades, el IV (vector d'inicialització) i la clau utilitzada per a l'encriptació.

    Args:
        key (bytes): Els bytes per generar la clau d'encriptació.
        data (bytes): Les dades a encriptar.

    Returns:
        Tuple[bytes, bytes, bytes]: Les dades encriptades, l'IV i la clau utilitzada per a l'encriptació.'''
    
    # Triar AES com a algoritme (128 bits = 16 bytes)
    key_length = 16  # AES-128
    encryption_key = key[:key_length]
    
    # Generar IV aleatori
    iv = get_random_bytes(16)  # AES utilitza blocs de 16 bytes
    
    # Crear el cipher AES en mode CBC
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)
    
    # Aplicar padding i encriptar les dades
    padded_data = pad(data, AES.block_size)
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, encryption_key