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
    
    # AES 키 길이 확인 (AES-128: 16바이트, AES-192: 24바이트, AES-256: 32바이트)
    # 문제 설명에 따라 키는 최소 64바이트 이상이어야 하므로, 필요한 길이에 맞는 접두사를 사용
    # 일반적으로 AES-256(32바이트)을 사용하는 것이 안전하므로 32바이트 키를 사용
    KEY_LENGTH = 32  # AES-256
    
    # 키가 충분히 긴지 확인
    if len(key) < 64:
        raise ValueError(f"Key must be at least 64 bytes long, got {len(key)} bytes")
    
    # 필요한 길이만큼 키의 접두사 사용
    encryption_key = key[:KEY_LENGTH]
    
    # 랜덤 IV 생성 (AES 블록 크기: 16바이트)
    iv = get_random_bytes(AES.block_size)
    
    # AES CBC 모드로 암호화 객체 생성
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)
    
    # 데이터 패딩 및 암호화
    # PKCS7 패딩 사용 (CBC 모드에서는 패딩이 필요함)
    padded_data = pad(data, AES.block_size)
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, encryption_key