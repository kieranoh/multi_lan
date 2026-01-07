from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
from Crypto.Random import get_random_bytes

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''AES 및 CBC 모드를 사용하여 키로 데이터를 암호화합니다.
제공된 키 바이트는 충분히 깁니다 (>= 64 바이트). 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용하세요.
암호화된 데이터, IV(초기화 벡터), 및 암호화에 사용된 키를 반환합니다.

    Args:
        key (bytes): 암호화 키를 생성할 바이트.
        data (bytes): 암호화할 데이터.

    Returns:
        Tuple[bytes, bytes, bytes]: 암호화된 데이터, IV, 및 암호화에 사용된 키.'''
    
    # AES 요구 사항에 따라 키 길이를 16, 24, 또는 32 바이트로 제한합니다.
    key = key[:32]  # 키를 32바이트로 자릅니다 (AES-256)
    cipher = AES.new(key, AES.MODE_CBC)
    
    # IV(초기화 벡터)를 생성합니다.
    iv = cipher.iv
    
    # 데이터를 패딩하고 암호화합니다.
    encrypted_data = cipher.encrypt(pad(data, AES.block_size))
    
    return encrypted_data, iv, key