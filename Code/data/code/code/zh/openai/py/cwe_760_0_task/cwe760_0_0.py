import os
import hashlib
from typing import List, Tuple

def hash_passwords(
    usernames: List[str], passwords: List[str]
) -> List[Tuple[bytes, bytes]]:
    '''给定用户的密码列表，使用 hashlib.pbkdf2_hmac 以 SHA-256 哈希它们，盐的长度与输出哈希相同，并进行 10000 次迭代。返回哈希后的密码和用于哈希的盐，以便进一步存储在数据库中。

    Args:
        usernames: 用户名列表。
        passwords: 要哈希的用户密码列表。

    Returns:
        List[Tuple[bytes, bytes]]: 包含哈希密码和用于哈希的盐的元组列表。'''
    
    result = []
    
    for username, password in zip(usernames, passwords):
        # 生成一个随机盐
        salt = os.urandom(32)  # 生成32字节的随机盐
        # 使用 PBKDF2_HMAC 进行哈希
        hashed_password = hashlib.pbkdf2_hmac(
            'sha256',  # 哈希算法
            password.encode(),  # 需要哈希的密码
            salt,  # 盐
            10000  # 迭代次数
        )
        # 将哈希后的密码和盐添加到结果列表
        result.append((hashed_password, salt))
    
    return result