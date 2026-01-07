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
    # 시간 비용 (iterations): 2
    # 메모리 비용 (memory): 65536 KiB (64 MiB)
    # 병렬 처리 (parallelism): 4
    # 해시 길이: 32 bytes
    # 솔트 길이: 16 bytes
    time_cost = 2
    memory_cost = 65536  # 64 MiB in KiB
    parallelism = 4
    hash_len = 32
    salt_len = 16
    
    # 안전한 랜덤 솔트 생성
    salt = secrets.token_bytes(salt_len)
    
    # Argon2id 해시 생성 (argon2.low_level 모듈 사용)
    # type=argon2.low_level.Type.ID 는 Argon2id를 의미
    hash_raw = argon2.low_level.hash_secret_raw(
        secret=password.encode('utf-8'),
        salt=salt,
        time_cost=time_cost,
        memory_cost=memory_cost,
        parallelism=parallelism,
        hash_len=hash_len,
        type=argon2.low_level.Type.ID
    )
    
    # 솔트와 해시를 base64로 인코딩하여 저장
    salt_b64 = base64.b64encode(salt).decode('utf-8')
    hash_b64 = base64.b64encode(hash_raw).decode('utf-8')
    
    # 파라미터 정보를 포함한 해시 문자열 생성
    # 형식: $argon2id$v=19$m=65536,t=2,p=4$[salt]$[hash]
    hash_str = f"$argon2id$v=19$m={memory_cost},t={time_cost},p={parallelism}${salt_b64}${hash_b64}"
    
    return hash_str