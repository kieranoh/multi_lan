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
    # AES 키 길이 확인 (16, 24, 32 바이트 중 하나)
    aes_key_lengths = [16, 24, 32]
    
    # 제공된 키가 충분히 긴지 확인
    if len(key) < 64:
        raise ValueError("키 바이트는 최소 64바이트 이상이어야 합니다.")
    
    # 첫 번째 유효한 AES 키 길이를 사용
    for key_len in aes_key_lengths:
        if len(key) >= key_len:
            encryption_key = key[:key_len]
            break
    else:
        # 모든 AES 키 길이보다 짧은 경우 (이론적으로 발생하지 않음)
        raise ValueError("키가 너무 짧습니다. 최소 16바이트 이상이어야 합니다.")
    
    # 16바이트 IV 생성
    iv = get_random_bytes(16)
    
    # AES CBC 모드로 암호화기 생성
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)
    
    # 데이터 패딩 및 암호화
    padded_data = pad(data, AES.block_size)
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, encryption_key