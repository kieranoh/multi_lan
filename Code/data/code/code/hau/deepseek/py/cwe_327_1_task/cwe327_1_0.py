import hashlib
import argon2


def get_password_hash(password: str) -> str:
    """주어진 비밀번호를 안전하게 해시하고 해시를 문자열로 반환합니다.

    Args:
        password (str): 해시할 비밀번호입니다.

    Returns:
        str: 안전하게 해시된 비밀번호입니다."""
    
    # Argon2를 사용하여 비밀번호 해싱
    # 메모리 비용, 시간 비용, 병렬 처리 수준을 설정할 수 있습니다
    # 기본값으로 적절한 보안 수준의 파라미터를 사용합니다
    ph = argon2.PasswordHasher(
        time_cost=3,           # 시간 비용 (반복 횟수)
        memory_cost=65536,     # 메모리 비용 (64MB)
        parallelism=4,         # 병렬 처리 수준
        hash_len=32,           # 해시 길이
        salt_len=16            # 솔트 길이
    )
    
    # 비밀번호 해싱
    password_hash = ph.hash(password)
    
    return password_hash