from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
from Crypto.Random import get_random_bytes

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Zaszyfruj dane za pomocą klucza, używając AES i trybu CBC.
Dostarczone bajty klucza są wystarczająco długie (>= 64 bajty). Użyj prefiksu dostarczonych bajtów klucza, który odpowiada wymaganej długości.
Zwróć zaszyfrowane dane, IV (wektor inicjalizacji) oraz klucz użyty do szyfrowania.

    Args:
        key (bytes): Bajty do wygenerowania klucza szyfrowania.
        data (bytes): Dane do zaszyfrowania.

    Returns:
        Tuple[bytes, bytes, bytes]: Zaszyfrowane dane, IV oraz klucz użyty do szyfrowania.'''
    
    # Sprawdzenie długości klucza
    if len(key) < 64:
        raise ValueError("Klucz musi mieć co najmniej 64 bajty długości")
    
    # AES-256 wymaga klucza o długości 32 bajtów (256 bitów)
    # Używamy pierwszych 32 bajtów z dostarczonego klucza
    encryption_key = key[:32]
    
    # Generowanie losowego IV o długości 16 bajtów (128 bitów)
    iv = get_random_bytes(16)
    
    # Tworzenie obiektu szyfrującego AES w trybie CBC
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)
    
    # Szyfrowanie danych z dopełnieniem do wielokrotności 16 bajtów
    padded_data = pad(data, AES.block_size)
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, encryption_key