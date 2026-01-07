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
    
    # 截取密钥到 32 字节，AES 支持的密钥长度为 16, 24, 或 32 字节
    encryption_key = key[:32]
    
    # 生成一个 16 字节的随机初始化向量
    iv = os.urandom(16)
    
    # 创建 AES 加密器
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)
    
    # 对数据进行填充和加密
    encrypted_data = cipher.encrypt(pad(data, AES.block_size))
    
    return encrypted_data, iv, encryption_key