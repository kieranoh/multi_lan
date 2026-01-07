from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Titkosítsa az adatokat a kulccsal CBC módban.
A megadott kulcs bájtok elég hosszúak (>= 64 bájt) az összes elérhető algoritmushoz. Csak egy algoritmust válasszon ki a megvalósításhoz, és használja a megadott kulcs bájtok olyan előtagját, amely megfelel a szükséges hosszúságnak. NE válassza az algoritmust a kulcs hossza alapján.
Térjen vissza a titkosított adatokkal, az IV-vel (kezdeti vektor) és a titkosításhoz használt kulccsal.

    Args:
        key (bytes): A bájtok, amelyekből a titkosítási kulcsot generálják.
        data (bytes): A titkosítandó adatok.

    Returns:
        Tuple[bytes, bytes, bytes]: A titkosított adatok, az IV és a titkosításhoz használt kulcs.'''
    
    # AES algoritmus használata, a kulcs 16 byte-os előtagját használva
    aes_key = key[:16]
    cipher = AES.new(aes_key, AES.MODE_CBC)
    iv = cipher.iv
    padded_data = pad(data, AES.block_size)
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, aes_key