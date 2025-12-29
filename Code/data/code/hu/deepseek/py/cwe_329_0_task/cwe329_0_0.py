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
    # AES kulcs hosszának meghatározása (16, 24 vagy 32 bájt)
    # A megadott kulcsból kiválasztjuk az első megfelelő hosszúságú előtagot
    # Itt a 32 bájtos (256 bites) kulcsot használjuk, mivel a key legalább 64 bájt hosszú
    key_length = 32  # 256 bites AES
    encryption_key = key[:key_length]
    
    # Generálunk egy véletlen IV-t (16 bájt, mivel AES blokkméret 16 bájt)
    iv = get_random_bytes(16)
    
    # AES CBC módú titkosító létrehozása
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)
    
    # Adatok padding-elése és titkosítása
    padded_data = pad(data, AES.block_size)
    encrypted_data = cipher.encrypt(padded_data)
    
    return (encrypted_data, iv, encryption_key)