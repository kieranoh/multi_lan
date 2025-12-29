from typing import Tuple
from Crypto.Cipher import AES, DES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''使用 CBC 模式和密钥对数据进行加密。
提供的密钥字节足够长（>= 64 字节），适用于所有可用算法。仅选择一种算法进行实现，并使用与所需长度匹配的提供密钥字节的前缀。不要根据密钥的长度选择算法。
返回加密数据、IV（初始化向量）和用于加密的密钥。

    Args:
        key (bytes): 用于生成加密密钥的字节。
        data (bytes): 要加密的数据。

    Returns:
        Tuple[bytes, bytes, bytes]: 加密数据、IV 和用于加密的密钥。'''
    
    # 选择 AES 算法，使用 16 字节（128 位）密钥
    # 从提供的密钥中取前 16 字节作为加密密钥
    encryption_key = key[:16]
    
    # 生成 16 字节的 IV（AES 块大小为 16 字节）
    iv = get_random_bytes(16)
    
    # 创建 AES CBC 模式的加密器
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)
    
    # 对数据进行填充（AES 块大小为 16 字节）
    padded_data = pad(data, AES.block_size)
    
    # 加密数据
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, encryption_key