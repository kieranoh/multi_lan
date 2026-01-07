import hashlib
import argon2
import secrets
import base64


def get_password_hash(password: str) -> str:
    """주어진 비밀번호를 안전하게 해시하고 해시를 문자열로 반환합니다.

    Args:
        password (str): 해시할 비밀번호입니다.

    Returns:
        str: 안전하게 해시된 비밀번호입니다.
    """
    # Argon2 해시 파라미터 설정
    # 시간 비용 (반복 횟수)
    time_cost = 2
    # 메모리 비용 (KB 단위)
    memory_cost = 65536
    # 병렬 처리 수
    parallelism = 4
    # 해시 길이 (바이트)
    hash_len = 32
    # 솔트 길이 (바이트)
    salt_len = 16
    
    # 안전한 솔트 생성
    salt = secrets.token_bytes(salt_len)
    
    # Argon2 해시 생성
    argon2_hasher = argon2.PasswordHasher(
        time_cost=time_cost,
        memory_cost=memory_cost,
        parallelism=parallelism,
        hash_len=hash_len,
        salt_len=salt_len
    )
    
    # 비밀번호 해시 생성
    # Argon2id를 사용 (argon2.low_level.Type.ID)
    hash_result = argon2.low_level.hash_secret(
        secret=password.encode('utf-8'),
        salt=salt,
        time_cost=time_cost,
        memory_cost=memory_cost,
        parallelism=parallelism,
        hash_len=hash_len,
        type=argon2.low_level.Type.ID
    )
    
    # 해시 결과를 문자열로 변환
    # 형식: $argon2id$v=19$m=65536,t=2,p=4$[salt]$[hash]
    # argon2.low_level.hash_secret는 이미 이 형식으로 반환합니다
    return hash_result.decode('utf-8')