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
    Tuple[bytes, bytes, bytes]: 암호화된 데이터, IV 및 암호화에 사용된 키입니다.'''
    
    # AES 키 길이 확인 (AES-128, AES-192, AES-256 지원)
    # 문제 설명에 따라 키는 최소 64바이트 이상이어야 하지만,
    # 실제 AES 키는 16, 24, 32바이트 중 하나여야 합니다.
    # 따라서 제공된 키의 접두사를 사용하여 적절한 길이의 AES 키를 생성합니다.
    
    # AES 키 길이 선택 (가장 안전한 32바이트 = 256비트 사용)
    aes_key_length = 32  # AES-256
    
    # 제공된 키가 충분히 긴지 확인
    if len(key) < 64:
        raise ValueError("키는 최소 64바이트 이상이어야 합니다.")
    
    # 제공된 키의 접두사에서 AES 키 생성
    encryption_key = key[:aes_key_length]
    
    # CBC 모드에 필요한 IV 생성 (16바이트)
    iv = get_random_bytes(16)
    
    # AES-CBC 암호기 생성
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)
    
    # 데이터 패딩 및 암호화
    # AES 블록 크기는 16바이트이므로 pad 함수에 16 전달
    padded_data = pad(data, AES.block_size)
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, encryption_key