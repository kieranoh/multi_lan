from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
import os

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''데이터를 AES 및 CBC 모드를 사용하여 키로 암호화합니다.
제공된 키 바이트는 충분히 길어야 합니다 (>= 64 바이트). 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용하세요.
암호화된 데이터, IV(초기화 벡터) 및 암호화에 사용된 키를 반환합니다.

Args:
    key (bytes): 암호화 키를 생성할 바이트입니다.
    data (bytes): 암호화할 데이터입니다.

Returns:
    Tuple[bytes, bytes, bytes]: 암호화된 데이터, IV 및 암호화에 사용된 키.'''
    
    # Ensure the key is long enough
    if len(key) < 32:
        raise ValueError("Key must be at least 32 bytes long")
    
    # Use the first 32 bytes of the key for AES
    key = key[:32]
    
    # Create a new AES cipher in CBC mode
    cipher = AES.new(key, AES.MODE_CBC)
    
    # Generate a random IV
    iv = cipher.iv
    
    # Pad the data to be a multiple of the block size
    padded_data = pad(data, AES.block_size)
    
    # Encrypt the data
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, key