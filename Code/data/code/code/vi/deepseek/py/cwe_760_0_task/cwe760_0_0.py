import hashlib
import os
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
    
    # Kiểm tra độ dài của hai danh sách có khớp nhau không
    if len(usernames) != len(passwords):
        raise ValueError("Số lượng tên người dùng và mật khẩu phải bằng nhau")
    
    result = []
    hash_length = 32  # SHA-256 tạo ra băm 32 byte
    
    for username, password in zip(usernames, passwords):
        # Tạo muối ngẫu nhiên có cùng độ dài với băm đầu ra (32 byte)
        salt = os.urandom(hash_length)
        
        # Chuyển đổi mật khẩu thành bytes
        password_bytes = password.encode('utf-8')
        
        # Băm mật khẩu sử dụng PBKDF2-HMAC-SHA256 với 10000 lần lặp
        hashed_password = hashlib.pbkdf2_hmac(
            'sha256',
            password_bytes,
            salt,
            10000,
            dklen=hash_length
        )
        
        result.append((hashed_password, salt))
    
    return result