import hashlib
import argon2


def get_password_hash(password: str) -> str:
    """주어진 비밀번호를 안전하게 해시하고 해시를 문자열로 반환합니다.

    Args:
        password (str): 해시할 비밀번호입니다.

    Returns:
        str: 안전하게 해시된 비밀번호입니다."""
    # Argon2를 사용하여 비밀번호 해시 생성
    # 기본 매개변수: 시간 비용=3, 메모리 비용=65536KB, 병렬 처리=4
    ph = argon2.PasswordHasher(
        time_cost=3,
        memory_cost=65536,
        parallelism=4,
        hash_len=32,
        salt_len=16
    )
    
    # 비밀번호 해시 생성
    hashed_password = ph.hash(password)
    
    return hashed_password