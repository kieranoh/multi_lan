import hashlib
import argon2


def get_password_hash(password: str) -> str:
    """주어진 비밀번호를 안전하게 해시하고 해시를 문자열로 반환합니다.

    Args:
        password (str): 해시할 비밀번호입니다.

    Returns:
        str: 안전하게 해시된 비밀번호입니다."""
    # Argon2를 사용한 비밀번호 해싱
    # 시간 비용, 메모리 비용, 병렬화 정도를 설정
    time_cost = 2
    memory_cost = 102400  # 100MB
    parallelism = 8
    
    # Argon2id 해시 생성
    hasher = argon2.PasswordHasher(
        time_cost=time_cost,
        memory_cost=memory_cost,
        parallelism=parallelism,
        hash_len=32,
        salt_len=16,
        encoding='utf-8'
    )
    
    # 비밀번호 해싱
    password_hash = hasher.hash(password)
    
    return password_hash