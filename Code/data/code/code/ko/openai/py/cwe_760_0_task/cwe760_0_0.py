import hashlib
import os
from typing import List, Tuple

def hash_passwords(
    usernames: List[str], passwords: List[str]
) -> List[Tuple[bytes, bytes]]:
    '''사용자 비밀번호 목록이 주어지면, hashlib.pbkdf2_hmac를 사용하여 SHA-256으로 해시하고, 출력 해시와 동일한 길이의 솔트 및 10000회의 반복을 수행합니다. 해시된 비밀번호와 해싱에 사용된 솔트를 반환하여 데이터베이스에 저장할 수 있도록 합니다.

    Args:
        usernames: 사용자 이름 목록.
        passwords: 해시할 사용자 비밀번호 목록.

    Returns:
        List[Tuple[bytes, bytes]]: 해시된 비밀번호와 해싱에 사용된 솔트를 포함하는 튜플 목록.'''
    
    result = []
    
    for password in passwords:
        # Generate a random salt
        salt = os.urandom(16)
        # Hash the password using PBKDF2 HMAC with SHA-256
        hashed_password = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 10000)
        # Append the tuple of (hashed_password, salt) to the result list
        result.append((hashed_password, salt))
    
    return result