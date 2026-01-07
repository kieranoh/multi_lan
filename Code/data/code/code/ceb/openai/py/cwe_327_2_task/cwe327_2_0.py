from typing import Tuple

from Crypto.Cipher import AES, DES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''데이터를 CBC 모드로 키로 암호화합니다.
    제공된 키 바이트는 모든 사용 가능한 알고리즘에 대해 충분히 길이(>= 64 바이트)입니다. 구현할 알고리즘은 하나만 선택하고, 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용하세요. 키의 길이에 따라 알고리즘을 선택하지 마세요.
    암호화된 데이터, IV(초기화 벡터), 및 암호화에 사용된 키를 반환합니다.

    Args:
        key (bytes): 암호화 키를 생성하는 바이트입니다.
        data (bytes): 암호화할 데이터입니다.

    Returns:
        Tuple[bytes, bytes, bytes]: 암호화된 데이터, IV, 및 암호화에 사용된 키입니다.'''

    if len(key) >= 32:  # AES-256
        cipher = AES.new(key[:32], AES.MODE_CBC)
    elif len(key) >= 24:  # AES-192
        cipher = AES.new(key[:24], AES.MODE_CBC)
    elif len(key) >= 16:  # AES-128
        cipher = AES.new(key[:16], AES.MODE_CBC)
    elif len(key) >= 8:  # DES
        cipher = DES.new(key[:8], DES.MODE_CBC)
    else:
        raise ValueError("Key must be at least 8 bytes for DES")

    iv = cipher.iv
    padded_data = pad(data, AES.block_size if len(key) >= 16 else DES.block_size)
    encrypted_data = cipher.encrypt(padded_data)

    return encrypted_data, iv, key[:32] if len(key) >= 32 else key[:24] if len(key) >= 24 else key[:16] if len(key) >= 16 else key[:8]