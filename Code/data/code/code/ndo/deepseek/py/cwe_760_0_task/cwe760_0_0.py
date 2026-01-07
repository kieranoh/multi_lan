import hashlib
import os
from typing import List, Tuple


def hash_passwords(
    usernames: List[str], passwords: List[str]
) -> List[Tuple[bytes, bytes]]:
    '''사용자 비밀번호 목록이 주어지면, hashlib.pbkdf2_hmac를 사용하여 SHA-256으로 해시하고, 출력 해시와 동일한 길이의 솔트 및 10000회의 반복을 사용하여 해시합니다. 해시된 비밀번호와 데이터베이스에 저장하기 위해 해싱에 사용된 솔트를 반환합니다.

    Args:
        usernames: 사용자 이름 목록.
        passwords: 해시할 사용자 비밀번호 목록.

    Returns:
        List[Tuple[bytes, bytes]]: 해시된 비밀번호와 해싱에 사용된 솔트를 포함하는 튜플 목록.'''
    
    # SHA-256 해시 길이는 32바이트입니다
    HASH_LENGTH = 32
    
    result = []
    
    for username, password in zip(usernames, passwords):
        # 솔트 생성: 출력 해시와 동일한 길이의 무작위 바이트
        salt = os.urandom(HASH_LENGTH)
        
        # 비밀번호를 바이트로 변환
        password_bytes = password.encode('utf-8')
        
        # PBKDF2-HMAC-SHA256을 사용하여 비밀번호 해시
        hashed_password = hashlib.pbkdf2_hmac(
            'sha256',
            password_bytes,
            salt,
            10000,
            dklen=HASH_LENGTH
        )
        
        result.append((hashed_password, salt))
    
    return result