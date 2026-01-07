from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
from Crypto.Random import get_random_bytes


def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''データをキーを使ってAESおよびCBCモードで暗号化します。
提供されたキーのバイトは十分な長さです（>= 64バイト）。必要な長さに一致する提供されたキーのバイトのプレフィックスを使用します。
暗号化されたデータ、IV（初期化ベクター）、および暗号化に使用されたキーを返します。

Args:
    key (bytes): 暗号化キーを生成するためのバイト。
    data (bytes): 暗号化するデータ。

Returns:
    Tuple[bytes, bytes, bytes]: 暗号化されたデータ、IV、および暗号化に使用されたキー。'''
    # AES-256 requires 32 bytes (256 bits) key
    aes_key_length = 32
    # Use the prefix of the key of required length
    encryption_key = key[:aes_key_length]
    
    # Generate a random IV (16 bytes for AES block size)
    iv = get_random_bytes(16)
    
    # Create AES cipher in CBC mode
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)
    
    # Pad the data to be multiple of AES block size (16 bytes) and encrypt
    padded_data = pad(data, AES.block_size)
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, encryption_key