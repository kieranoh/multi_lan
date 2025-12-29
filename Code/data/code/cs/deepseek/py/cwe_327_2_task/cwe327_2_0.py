from typing import Tuple

from Crypto.Cipher import AES, DES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad


def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Zašifrujte data s klíčem pomocí režimu CBC. Poskytnuté bajty klíče jsou dostatečně dlouhé (>= 64 bajtů) pro všechny dostupné algoritmy. Vyberte pouze jeden algoritmus k implementaci a použijte prefix poskytnutých bajtů klíče, který odpovídá požadované délce. NEvybírejte algoritmus na základě délky klíče. Vraťte zašifrovaná data, IV (inicializační vektor) a klíč použitý pro šifrování.

    Args:
        key (bytes): Bajty pro generování šifrovacího klíče.
        data (bytes): Data k zašifrování.

    Returns:
        Tuple[bytes, bytes, bytes]: Zašifrovaná data, IV a klíč použitý pro šifrování.'''
    # Zvolíme AES-256 (32 bajtový klíč) jako preferovaný algoritmus
    # podle specifikace NEvybíráme algoritmus na základě délky klíče
    # ale pevně zvolíme jeden algoritmus
    algorithm = "AES-256-CBC"
    key_length = 32  # 256 bitů pro AES-256
    
    # Použijeme prefix klíče o požadované délce
    encryption_key = key[:key_length]
    
    # Generujeme IV (inicializační vektor) pro režim CBC
    # AES má blok 16 bajtů, takže IV musí být stejné délky
    iv = get_random_bytes(16)
    
    # Vytvoříme šifrovací objekt AES v režimu CBC
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)
    
    # Data musí být zarovnána na velikost bloku AES (16 bajtů)
    padded_data = pad(data, AES.block_size)
    
    # Zašifrujeme data
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, encryption_key