import hashlib
import argon2


def get_password_hash(password: str) -> str:
    """주어진 비밀번호를 안전하게 해시하고 해시를 문자열로 반환합니다.

    Args:
        password (str): 해시할 비밀번호입니다.

    Returns:
        str: 안전하게 해시된 비밀번호입니다."""
    # Argon2 해시 생성
    hasher = argon2.PasswordHasher(
        time_cost=3,  # 반복 횟수
        memory_cost=65536,  # 메모리 사용량 (KB)
        parallelism=4,  # 병렬 처리 수
        hash_len=32,  # 해시 길이
        salt_len=16  # 솔트 길이
    )
    
    # 비밀번호 해시 생성
    hashed_password = hasher.hash(password)
    
    return hashed_password