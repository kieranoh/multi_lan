from typing import Tuple
from Crypto.Cipher import AES, DES
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
    # Kies AES als algoritme (vastgelegde keuze, niet gebaseerd op sleutellengte)
    # AES vereist een sleutel van 16, 24 of 32 bytes
    # We kiezen voor 32 bytes (AES-256) voor maximale beveiliging
    key_length = 32
    encryption_key = key[:key_length]  # Gebruik het voorvoegsel van de opgegeven sleutelbytes
    
    # Genereer een willekeurige IV van de juiste grootte voor AES (16 bytes)
    iv = get_random_bytes(16)
    
    # Maak een AES-cipher object in CBC-modus
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)
    
    # Versleutel de gegevens (pad toevoegen voor CBC-modus)
    # AES blokgrootte is 16 bytes
    padded_data = pad(data, AES.block_size)
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, encryption_key