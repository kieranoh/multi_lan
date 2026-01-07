import hashlib
import argon2


def get_password_hash(password: str) -> str:
    """주어진 비밀번호를 안전하게 해시하고 해시를 문자열로 반환합니다.

    Args:
        password (str): 해시할 비밀번호입니다.

    Returns:
        str: 안전하게 해시된 비밀번호입니다.
    """
    # Argon2 해시 생성
    # 시간 비용, 메모리 비용, 병렬 처리 수준 설정
    time_cost = 2
    memory_cost = 102400  # 100MB
    parallelism = 8
    hash_length = 32
    salt_length = 16
    
    # Argon2 해시 생성
    ph = argon2.PasswordHasher(
        time_cost=time_cost,
        memory_cost=memory_cost,
        parallelism=parallelism,
        hash_len=hash_length,
        salt_len=salt_length
    )
    
    # 비밀번호 해시
    password_hash = ph.hash(password)
    
    return password_hash