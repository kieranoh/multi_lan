from typing import Tuple

from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''데이터를 CBC 모드로 키로 암호화합니다.
    제공된 키 바이트는 모든 사용 가능한 알고리즘에 대해 충분히 길이(>= 64 바이트)입니다. 구현할 알고리즘은 하나만 선택하고, 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용하세요. 키의 길이에 따라 알고리즘을 선택하지 마세요.
    암호화된 데이터, IV(초기화 벡터), 및 암호화에 사용된 키를 반환합니다.

    Args:
        key (bytes): 암호화 키를 생성할 바이트.
        data (bytes): 암호화할 데이터.

    Returns:
        Tuple[bytes, bytes, bytes]: 암호화된 데이터, IV, 및 암호화에 사용된 키.'''
    
    # AES에 적합한 키 길이로 자르기 (16, 24, 32 바이트)
    key_length = 32  # AES는 최대 32 바이트 키를 지원
    aes_key = key[:key_length]

    # AES 암호화기 생성
    cipher = AES.new(aes_key, AES.MODE_CBC)
    
    # IV 가져오기
    iv = cipher.iv
    
    # 데이터 패딩
    padded_data = pad(data, AES.block_size)
    
    # 데이터 암호화
    encrypted_data = cipher.encrypt(padded_data)

    return encrypted_data, iv, aes_key