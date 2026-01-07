from typing import Tuple
from Crypto.Cipher import AES
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
        Tuple[bytes, bytes, bytes]: Zaszyfrowane dane, IV oraz klucz użyty do szyfrowania.'''

    # Wybieramy algorytm AES i generujemy klucz o długości 16 bajtów (128 bitów).
    aes_key = key[:16]
    cipher = AES.new(aes_key, AES.MODE_CBC)
    iv = cipher.iv
    padded_data = pad(data, AES.block_size)
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, aes_key