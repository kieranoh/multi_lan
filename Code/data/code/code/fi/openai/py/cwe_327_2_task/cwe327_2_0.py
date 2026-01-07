from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Salakirjoita tiedot avaimella käyttäen CBC-tilaa.
    Annetut avainbittit ovat tarpeeksi pitkiä (>= 64 tavua) kaikille saatavilla oleville algoritmeille. Valitse vain yksi algoritmi toteutettavaksi ja käytä annettujen avainbittien prefiksiä, joka vastaa vaadittua pituutta. Älä valitse algoritmia avaimen pituuden perusteella.
    Palauta salattu data, IV (alkuvarausvektori) ja avain, jota käytettiin salaukseen.

    Args:
        key (bytes): Tavut salausavaimen luomiseksi.
        data (bytes): Salattava data.

    Returns:
        Tuple[bytes, bytes, bytes]: Salattu data, IV ja avain, jota käytettiin salaukseen.'''
    
    # Määritä AES-algoritmi
    cipher = AES.new(key[:32], AES.MODE_CBC)  # Käytä 256-bittistä avainta
    iv = cipher.iv  # Hanki alkuvarausvektori
    padded_data = pad(data, AES.block_size)  # Täytä data AES:n lohkokokoon
    encrypted_data = cipher.encrypt(padded_data)  # Salakirjoita data
    
    return encrypted_data, iv, key