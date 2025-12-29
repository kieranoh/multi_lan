from typing import Tuple
from Crypto.Cipher import AES, DES
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
    # Rögzített algoritmus választása (AES-256)
    algorithm = 'AES'
    key_length = 32  # AES-256-hoz 32 bájt (256 bit)
    
    # Kulcs kivágása a megadott bájtokból a szükséges hosszúságra
    encryption_key = key[:key_length]
    
    # IV generálása (AES blokkméret: 16 bájt)
    iv = get_random_bytes(16)
    
    # Cipher létrehozása CBC módban
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)
    
    # Adatok padding-elése és titkosítása
    padded_data = pad(data, AES.block_size)
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, encryption_key