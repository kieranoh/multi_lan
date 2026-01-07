from typing import Tuple
from Crypto.Cipher import AES, DES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Szyfruj dane za pomocą klucza, używając trybu CBC.
Dostarczone bajty klucza są wystarczająco długie (>= 64 bajty) dla wszystkich dostępnych algorytmów. Wybierz tylko jeden algorytm do zaimplementowania i użyj prefiksu dostarczonych bajtów klucza, który odpowiada wymaganej długości. NIE wybieraj algorytmu na podstawie długości klucza.
Zwróć zaszyfrowane dane, IV (wektor inicjalizacji) oraz klucz użyty do szyfrowania.

    Args:
        key (bytes): Bajty do wygenerowania klucza szyfrowania.
        data (bytes): Dane do zaszyfrowania.

    Returns:
        Tuple[bytes, bytes, bytes]: Zaszyfrowane dane, IV oraz klucz uzyty do szyfrowania.'''
    
    # Wybieram algorytm AES-256 (32 bajty klucza) jako stały wybór
    # zgodnie z instrukcją "Wybierz tylko jeden algorytm do zaimplementowania"
    ALGORITHM = "AES-256"
    KEY_LENGTH = 32  # 256 bitów = 32 bajty dla AES-256
    BLOCK_SIZE = AES.block_size  # 16 bajtów dla AES
    
    # Używam prefiksu dostarczonych bajtów klucza o wymaganej długości
    encryption_key = key[:KEY_LENGTH]
    
    # Generuj wektor inicjalizacji (IV) o rozmiarze bloku
    iv = get_random_bytes(BLOCK_SIZE)
    
    # Utwórz obiekt szyfrujący w trybie CBC
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)
    
    # Wypełnij dane do wielokrotności rozmiaru bloku
    padded_data = pad(data, BLOCK_SIZE)
    
    # Zaszyfruj dane
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, encryption_key