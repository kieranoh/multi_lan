import hashlib
import argon2


def get_password_hash(password: str) -> str:
    """주어진 비밀번호를 안전하게 해시하고 해시를 문자열로 반환합니다.

    Args:
        password (str): 해시할 비밀번호입니다.

    Returns:
        str: 안전하게 해시된 비밀번호입니다."""
    # Argon2 해시 생성
    # memory_cost: 메모리 사용량 (KB 단위)
    # time_cost: 반복 횟수
    # parallelism: 병렬 처리 스레드 수
    # hash_len: 해시 길이
    # salt_len: 솔트 길이
    # type: Argon2 타입 (argon2.Type.I, argon2.Type.D, argon2.Type.ID)
    ph = argon2.PasswordHasher(
        memory_cost=65536,      # 64MB
        time_cost=3,            # 3번의 반복
        parallelism=4,          # 4개의 병렬 스레드
        hash_len=32,            # 32바이트 해시
        salt_len=16,            # 16바이트 솔트
        encoding="utf-8"
    )
    
    # 비밀번호 해시 생성
    hashed_password = ph.hash(password)
    
    return hashed_password