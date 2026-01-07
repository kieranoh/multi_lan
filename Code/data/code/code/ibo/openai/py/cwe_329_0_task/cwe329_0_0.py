from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
import os

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''데이터를 AES 및 CBC 모드를 사용하여 키로 암호화합니다.
    제공된 키 바이트는 충분히 길어야 합니다 (>= 64 바이트). 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용하세요.
    암호화에 사용된 암호화된 데이터, IV(초기화 벡터) 및 키를 반환합니다.

    Args:
        key (bytes): 암호화 키를 생성할 바이트입니다.
        data (bytes): 암호화할 데이터입니다.

    Returns:
        Tuple[bytes, bytes, bytes]: 암호화된 데이터, IV 및 암호화에 사용된 키입니다.'''
    
    # 키의 길이를 32 바이트로 제한 (AES-256을 위한 길이)
    key = key[:32]
    
    # 초기화 벡터(IV) 생성
    iv = os.urandom(AES.block_size)
    
    # AES 암호 객체 생성
    cipher = AES.new(key, AES.MODE_CBC, iv)
    
    # 데이터 패딩 및 암호화
    encrypted_data = cipher.encrypt(pad(data, AES.block_size))
    
    return encrypted_data, iv, key