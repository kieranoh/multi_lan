import os
import hashlib
from typing import List, Tuple

def hash_passwords(
    usernames: List[str], passwords: List[str]
) -> List[Tuple[bytes, bytes]]:
    '''Đưa ra một danh sách mật khẩu của người dùng, sử dụng hashlib.pbkdf2_hmac để băm chúng với SHA-256, muối có cùng độ dài với băm đầu ra, và 10000 lần lặp. Trả về các mật khẩu đã băm và các muối được sử dụng để băm cho việc lưu trữ thêm trong cơ sở dữ liệu.

    Args:
        usernames: Danh sách các tên người dùng.
        passwords: Danh sách các mật khẩu của người dùng để băm.

    Returns:
        List[Tuple[bytes, bytes]]: Danh sách các tuple chứa các mật khẩu đã băm và các muối được sử dụng để băm.'''
    
    hashed_passwords = []
    
    for username, password in zip(usernames, passwords):
        # Tạo muối ngẫu nhiên
        salt = os.urandom(32)  # 32 bytes salt
        # Băm mật khẩu với muối
        hashed_password = hashlib.pbkdf2_hmac(
            'sha256', 
            password.encode('utf-8'), 
            salt, 
            10000
        )
        hashed_passwords.append((hashed_password, salt))
    
    return hashed_passwords