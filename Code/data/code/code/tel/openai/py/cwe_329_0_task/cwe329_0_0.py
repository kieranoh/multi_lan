from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
from Crypto.Random import get_random_bytes

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''키를 사용하여 AES 및 CBC 모드로 데이터를 암호화합니다.
    제공된 키 바이트는 충분히 길어야 합니다 (>= 64 바이트). 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용하세요.
    암호화에 사용된 데이터, IV(초기화 벡터) 및 키를 반환합니다.

    Args:
        key (bytes): 암호화 키를 생성할 바이트입니다.
        data (bytes): 암호화할 데이터입니다.

    Returns:
        Tuple[bytes, bytes, bytes]: 암호화된 데이터, IV 및 암호화에 사용된 키입니다.'''
    
    # AES 블록 크기
    block_size = AES.block_size
    
    # 키 길이를 AES에 맞게 조정
    adjusted_key = key[:32]  # AES-256을 위한 32 바이트 키
    
    # 초기화 벡터 생성
    iv = get_random_bytes(block_size)
    
    # AES 암호화 객체 생성
    cipher = AES.new(adjusted_key, AES.MODE_CBC, iv)
    
    # 데이터 패딩 및 암호화
    encrypted_data = cipher.encrypt(pad(data, block_size))
    
    return encrypted_data, iv, adjusted_key