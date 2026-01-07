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
    
    # AES-256 requires 32 bytes key, so we take the first 32 bytes from the provided key
    # The docstring mentions the key should be >= 64 bytes, but we only need 32 for AES-256
    # We'll use 32 bytes for AES-256 as it's a common secure choice
    aes_key_length = 32
    
    # Check if the provided key is long enough
    if len(key) < aes_key_length:
        raise ValueError(f"Key must be at least {aes_key_length} bytes long")
    
    # Extract the first 32 bytes as the AES key
    aes_key = key[:aes_key_length]
    
    # Generate a random IV (16 bytes for AES)
    iv = get_random_bytes(16)
    
    # Create AES cipher in CBC mode
    cipher = AES.new(aes_key, AES.MODE_CBC, iv)
    
    # Pad the data to be multiple of AES block size (16 bytes) and encrypt
    padded_data = pad(data, AES.block_size)
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, aes_key