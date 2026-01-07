from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
from Crypto.Random import get_random_bytes

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''데이터를 AES 및 CBC 모드를 사용하여 키로 암호화합니다.
제공된 키 바이트는 충분히 길어야 합니다 (>= 64 바이트). 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용하세요.
암호화된 데이터, IV(초기화 벡터) 및 암호화에 사용된 키를 반환합니다.

Args:
    key (bytes): 암호화 키를 생성할 바이트입니다.
    data (bytes): 암호화할 데이터입니다.

Returns:
    Tuple[bytes, bytes, bytes]: 암호화된 데이터, IV 및 암호화에 사용된 키.'''
    # AES 키 길이 확인 (AES-256 사용을 위해 32바이트 필요)
    required_key_length = 32  # AES-256
    
    # 키 길이가 충분한지 확인
    if len(key) < required_key_length:
        raise ValueError(f"키가 너무 짧습니다. 최소 {required_key_length}바이트가 필요하지만 {len(key)}바이트가 제공되었습니다.")
    
    # 필요한 길이만큼 키의 접두사 사용
    encryption_key = key[:required_key_length]
    
    # 16바이트 IV 생성
    iv = get_random_bytes(16)
    
    # AES CBC 모드로 암호화기 생성
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)
    
    # 데이터를 패딩하여 암호화 (AES 블록 크기: 16바이트)
    padded_data = pad(data, AES.block_size)
    
    # 데이터 암호화
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, encryption_key