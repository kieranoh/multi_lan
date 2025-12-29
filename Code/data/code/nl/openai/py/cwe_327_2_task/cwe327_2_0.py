from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad


def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Versleutel de gegevens met de sleutel met behulp van CBC-modus.
    De opgegeven sleutelbytes zijn lang genoeg (>= 64 bytes) voor alle beschikbare algoritmen. Kies slechts één algoritme om te implementeren en gebruik het voorvoegsel van de opgegeven sleutelbytes dat overeenkomt met de vereiste lengte. Kies het algoritme NIET op basis van de lengte van de sleutel.
    Geef de versleutelde gegevens, de IV (initialisatievector) en de sleutel die voor versleuteling is gebruikt terug.

    Args:
        key (bytes): De bytes om de versleutelingssleutel te genereren.
        data (bytes): De te versleutelen gegevens.

    Returns:
        Tuple[bytes, bytes, bytes]: De versleutelde gegevens, de IV en de sleutel die voor versleuteling is gebruikt.'''

    iv = get_random_bytes(16)  # IV moet 16 bytes zijn voor AES
    aes_key = key[:32]  # Neem de eerste 32 bytes van de sleutel voor AES
    cipher = AES.new(aes_key, AES.MODE_CBC, iv)
    encrypted_data = cipher.encrypt(pad(data, AES.block_size))
    
    return encrypted_data, iv, aes_key