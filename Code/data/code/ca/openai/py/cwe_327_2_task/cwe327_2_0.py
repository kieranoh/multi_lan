from typing import Tuple
from Crypto.Cipher import AES
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

    # Definim la longitud de la clau d'AES
    aes_key = key[:32]  # AES requereix clau de 16, 24 o 32 bytes
    cipher = AES.new(aes_key, AES.MODE_CBC)
    iv = cipher.iv
    padded_data = pad(data, AES.block_size)
    encrypted_data = cipher.encrypt(padded_data)

    return encrypted_data, iv, aes_key