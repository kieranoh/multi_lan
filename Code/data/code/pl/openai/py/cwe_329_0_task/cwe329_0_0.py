from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
import os

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Zaszyfruj dane za pomocą klucza, używając AES i trybu CBC.
Dostarczone bajty klucza są wystarczająco długie (>= 64 bajty). Użyj prefiksu dostarczonych bajtów klucza, który odpowiada wymaganej długości.
Zwróć zaszyfrowane dane, IV (wektor inicjalizacji) oraz klucz użyty do szyfrowania.

    Args:
        key (bytes): Bajty do wygenerowania klucza szyfrowania.
        data (bytes): Dane do zaszyfrowania.

    Returns:
        Tuple[bytes, bytes, bytes]: Zaszyfrowane dane, IV oraz klucz użyty do szyfrowania.'''
    
    # Wybierz odpowiednią długość klucza AES (16, 24 lub 32 bajty)
    key_length = 32  # Użyj 32 bajtów (256 bitów)
    encryption_key = key[:key_length]  # Użyj prefiksu klucza

    # Inicjalizuj wektor inicjalizacji (IV)
    iv = os.urandom(AES.block_size)  # 16 bajtów dla AES

    # Inicjalizuj szyfrator AES w trybie CBC
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)

    # Szyfruj dane
    padded_data = pad(data, AES.block_size)  # Paduj dane
    encrypted_data = cipher.encrypt(padded_data)

    return encrypted_data, iv, encryption_key