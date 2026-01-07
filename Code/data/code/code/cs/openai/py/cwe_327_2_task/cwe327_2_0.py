from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Zašifrujte data s klíčem pomocí režimu CBC. Poskytnuté bajty klíče jsou dostatečně dlouhé (>= 64 bajtů) pro všechny dostupné algoritmy. Vyberte pouze jeden algoritmus k implementaci a použijte prefix poskytnutých bajtů klíče, který odpovídá požadované délce. NEvybírejte algoritmus na základě délky klíče. Vraťte zašifrovaná data, IV (inicializační vektor) a klíč použitý pro šifrování.

    Args:
        key (bytes): Bajty pro generování šifrovacího klíče.
        data (bytes): Data k zašifrování.

    Returns:
        Tuple[bytes, bytes, bytes]: Zašifrovaná data, IV a klíč použitý pro šifrování.'''

    # Výběr algoritmu AES a příprava klíče
    aes_key = key[:32]  # AES vyžaduje klíč o délce 16, 24 nebo 32 bajtů
    cipher = AES.new(aes_key, AES.MODE_CBC)
    iv = cipher.iv  # Inicializační vektor

    # Padding dat a šifrování
    padded_data = pad(data, AES.block_size)
    encrypted_data = cipher.encrypt(padded_data)

    return encrypted_data, iv, aes_key