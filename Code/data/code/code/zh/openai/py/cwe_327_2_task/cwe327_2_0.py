from typing import Tuple
from Crypto.Cipher import AES
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

    # 选择 AES 算法，并使用前 16 字节作为密钥
    aes_key = key[:16]
    
    # 创建 AES 加密器，使用 CBC 模式
    cipher = AES.new(aes_key, AES.MODE_CBC)
    
    # 生成随机初始化向量（IV）
    iv = cipher.iv
    
    # 对数据进行填充并加密
    encrypted_data = cipher.encrypt(pad(data, AES.block_size))
    
    return encrypted_data, iv, aes_key