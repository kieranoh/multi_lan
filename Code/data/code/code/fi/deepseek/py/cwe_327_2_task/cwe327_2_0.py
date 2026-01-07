from typing import Tuple
from Crypto.Cipher import AES, DES
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
    
    # Valitaan AES algoritmi (käyttää 16, 24 tai 32 tavun avaimia)
    # Otetaan 16 tavun pituinen prefiksi annetusta avaimesta AES-128:lle
    encryption_key = key[:16]
    
    # Luodaan satunnainen IV (Initialization Vector) CBC-tilaa varten
    # AES:n lohkoko on 16 tavua, joten IV:n pituus on 16 tavua
    iv = get_random_bytes(16)
    
    # Luodaan AES-salain CBC-tilassa annetulla avaimella ja IV:llä
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)
    
    # Suoritetaan salaus
    # Data täytetään ennen salausta, koska CBC vaatii datan olevan lohkokoon monikerta
    padded_data = pad(data, AES.block_size)
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, encryption_key