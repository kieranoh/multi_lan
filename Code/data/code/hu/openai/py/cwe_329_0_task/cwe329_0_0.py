from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
from Crypto.Random import get_random_bytes

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Titkosítsa az adatokat a kulccsal AES és CBC módban.
A megadott kulcs bájtok elég hosszúak (>= 64 bájt). Használja a megadott kulcs bájtok olyan előtagját, amely megfelel a szükséges hosszúságnak.
Adja vissza a titkosított adatokat, az IV-t (kezdeti vektor) és a titkosításhoz használt kulcsot.

    Args:
        key (bytes): A titkosítási kulcs generálásához szükséges bájtok.
        data (bytes): A titkosítandó adatok.

    Returns:
        Tuple[bytes, bytes, bytes]: A titkosított adatok, az IV és a titkosításhoz használt kulcs.'''
    
    # Truncate or use the first 16 bytes of the key
    key = key[:16]
    
    # Generate a random initialization vector
    iv = get_random_bytes(AES.block_size)
    
    # Create AES cipher in CBC mode
    cipher = AES.new(key, AES.MODE_CBC, iv)
    
    # Pad the data and encrypt
    encrypted_data = cipher.encrypt(pad(data, AES.block_size))
    
    return encrypted_data, iv, key