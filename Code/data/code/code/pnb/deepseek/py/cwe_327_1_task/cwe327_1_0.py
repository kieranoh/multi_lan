import hashlib
import argon2
import secrets
import base64
from typing import Tuple


def get_password_hash(password: str) -> str:
    """주어진 비밀번호를 안전하게 해시하고 해시를 문자열로 반환합니다.

    Args:
        password (str): 해시할 비밀번호입니다.

    Returns:
        str: 안전하게 해시된 비밀번호입니다.
    """
    # 솔트 생성 (16바이트)
    salt = secrets.token_bytes(16)
    
    # Argon2id를 사용한 해시 생성
    # 기본 매개변수: 시간 비용=2, 메모리 비용=65536KB (64MB), 병렬 처리=4
    hasher = argon2.PasswordHasher(
        time_cost=2,
        memory_cost=65536,
        parallelism=4,
        hash_len=32,
        salt_len=16,
        encoding='utf-8'
    )
    
    # 비밀번호 해시 생성
    password_hash = hasher.hash(password, salt=salt)
    
    return password_hash


def verify_password_hash(password: str, hashed_password: str) -> bool:
    """저장된 해시와 비교하여 비밀번호를 검증합니다.
    
    Args:
        password (str): 검증할 비밀번호입니다.
        hashed_password (str): 저장된 해시 문자열입니다.
        
    Returns:
        bool: 비밀번호가 일치하면 True, 그렇지 않으면 False입니다.
    """
    try:
        hasher = argon2.PasswordHasher()
        return hasher.verify(hashed_password, password)
    except (argon2.exceptions.VerifyMismatchError, 
            argon2.exceptions.VerificationError,
            argon2.exceptions.InvalidHashError):
        return False


def get_legacy_password_hash(password: str) -> str:
    """레거시 시스템과의 호환성을 위한 SHA-256 해시 함수입니다.
    
    Args:
        password (str): 해시할 비밀번호입니다.
        
    Returns:
        str: SHA-256 해시 문자열입니다.
    """
    # 솔트 생성 및 해시
    salt = secrets.token_hex(16)
    salted_password = password + salt
    hash_object = hashlib.sha256(salted_password.encode())
    hash_hex = hash_object.hexdigest()
    
    # 형식: 알고리즘$솔트$해시
    return f"sha256${salt}${hash_hex}"