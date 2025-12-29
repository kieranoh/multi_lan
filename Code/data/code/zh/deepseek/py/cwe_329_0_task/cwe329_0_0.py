from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
import os

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''使用 AES 和 CBC 模式对数据进行加密。
提供的密钥字节长度足够（>= 64 字节）。使用与所需长度匹配的提供密钥字节的前缀。
返回加密数据、IV（初始化向量）和用于加密的密钥。

    Args:
        key (bytes): 用于生成加密密钥的字节。
        data (bytes): 要加密的数据。

    Returns:
        Tuple[bytes, bytes, bytes]: 加密数据、IV 和用于加密的密钥。'''
    
    # AES 密钥长度可以是 16, 24 或 32 字节（对应 AES-128, AES-192, AES-256）
    # 根据文档说明，提供的密钥长度足够（>= 64 字节），我们使用前 32 字节作为 AES-256 密钥
    aes_key_length = 32  # 使用 AES-256
    aes_key = key[:aes_key_length]
    
    # 生成随机的 16 字节 IV（AES 块大小）
    iv = os.urandom(16)
    
    # 创建 AES-CBC 加密器
    cipher = AES.new(aes_key, AES.MODE_CBC, iv)
    
    # 对数据进行填充并加密
    # AES 块大小为 16 字节，所以使用 pkcs7 填充到 16 字节的倍数
    padded_data = pad(data, AES.block_size)
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, aes_key