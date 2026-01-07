from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
from Crypto.Random import get_random_bytes

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''데이터를 AES 및 CBC 모드를 사용하여 키로 암호화합니다.
제공된 키 바이트는 충분히 길어야 합니다 (>= 64 바이트). 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용하세요.
암호화에 사용된 암호화된 데이터, IV(초기화 벡터) 및 키를 반환합니다.

Args:
    key (bytes): 암호화 키를 생성할 바이트입니다.
    data (bytes): 암호화할 데이터입니다.

Returns:
    Tuple[bytes, bytes, bytes]: 암호화된 데이터, IV 및 암호화에 사용된 키입니다.'''
    
    # 키가 64바이트보다 클 경우 접두사로 사용
    key = key[:32]  # AES는 16, 24, 32바이트 키 길이만 지원
    iv = get_random_bytes(AES.block_size)  # 초기화 벡터 생성
    cipher = AES.new(key, AES.MODE_CBC, iv)  # AES 암호화 객체 생성
    encrypted_data = cipher.encrypt(pad(data, AES.block_size))  # 데이터 암호화

    return encrypted_data, iv, key  # 암호화된 데이터, IV, 키 반환