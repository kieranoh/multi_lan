import hashlib
import os
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
    
    # 获取SHA-256哈希的长度（以字节为单位）
    hash_length = hashlib.sha256().digest_size
    
    for username, password in zip(usernames, passwords):
        # 生成与哈希长度相同的盐
        salt = os.urandom(hash_length)
        
        # 使用PBKDF2-HMAC-SHA256进行密码哈希
        hashed_password = hashlib.pbkdf2_hmac(
            'sha256',
            password.encode('utf-8'),
            salt,
            10000,
            dklen=hash_length
        )
        
        result.append((hashed_password, salt))
    
    return result