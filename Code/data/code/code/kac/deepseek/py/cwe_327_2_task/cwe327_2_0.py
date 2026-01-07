from typing import Tuple
from Crypto.Cipher import AES, DES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad


def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''키를 사용하여 CBC 모드로 데이터를 암호화합니다.
제공된 키 바이트는 모든 사용 가능한 알고리즘에 대해 충분히 길이(>= 64 바이트)입니다. 구현할 알고리즘은 하나만 선택하고, 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용하세요. 키의 길이에 따라 알고리즘을 선택하지 마세요.
암호화된 데이터, IV(초기화 벡터), 및 암호화에 사용된 키를 반환합니다.

Args:
    key (bytes): 암호화 키를 생성할 바이트입니다.
    data (bytes): 암호화할 데이터입니다.

Returns:
    Tuple[bytes, bytes, bytes]: 암호화된 데이터, IV, 및 암호화에 사용된 키.'''
    # AES-256을 사용하기로 선택 (키 길이: 32바이트)
    algorithm_key_length = 32
    
    # 제공된 키에서 필요한 길이만큼 접두사 사용
    encryption_key = key[:algorithm_key_length]
    
    # AES 블록 크기에 맞춰 IV 생성
    iv = get_random_bytes(AES.block_size)
    
    # AES CBC 모드로 암호화기 생성
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)
    
    # 데이터를 패딩하여 암호화
    padded_data = pad(data, AES.block_size)
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, encryption_key