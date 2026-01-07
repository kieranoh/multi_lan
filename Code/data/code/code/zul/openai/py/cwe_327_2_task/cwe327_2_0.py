from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''데이터를 CBC 모드로 키로 암호화합니다.
제공된 키 바이트는 모든 사용 가능한 알고리즘에 대해 충분히 길이(>= 64 바이트)입니다. 구현할 알고리즘을 하나만 선택하고, 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용하세요. 키의 길이에 따라 알고리즘을 선택하지 마세요.
암호화된 데이터, IV(초기화 벡터), 및 암호화에 사용된 키를 반환합니다.

Args:
    key (bytes): 암호화 키를 생성할 바이트입니다.
    data (bytes): 암호화할 데이터입니다.

Returns:
    Tuple[bytes, bytes, bytes]: 암호화된 데이터, IV, 및 암호화에 사용된 키입니다.'''

    # AES 사용을 위해 16 바이트 키로 자름
    aes_key = key[:16]  # AES에서 사용하는 128비트 키
    cipher = AES.new(aes_key, AES.MODE_CBC)  # CBC 모드로 AES 암호화기 생성
    iv = cipher.iv  # 초기화 벡터
    ciphertext = cipher.encrypt(pad(data, AES.block_size))  # 데이터 암호화 및 패딩 추가

    return ciphertext, iv, aes_key