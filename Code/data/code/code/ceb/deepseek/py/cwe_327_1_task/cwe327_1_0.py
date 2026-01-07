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
    # 메모리 비용 (KiB 단위) - 64MB
    memory_cost = 65536
    # 시간 비용 (반복 횟수)
    time_cost = 3
    # 병렬 처리 수
    parallelism = 4
    # 해시 길이 (바이트)
    hash_len = 32
    # 솔트 길이 (바이트)
    salt_len = 16
    
    # 안전한 무작위 솔트 생성
    salt = secrets.token_bytes(salt_len)
    
    # Argon2id 해시 생성 (argon2.low_level 사용)
    # type=argon2.low_level.Type.ID는 Argon2id를 의미
    hash_bytes = argon2.low_level.hash_secret(
        secret=password.encode('utf-8'),
        salt=salt,
        time_cost=time_cost,
        memory_cost=memory_cost,
        parallelism=parallelism,
        hash_len=hash_len,
        type=argon2.low_level.Type.ID
    )
    
    # 해시 결과에서 실제 해시 값 추출
    # argon2.low_level.hash_secret는 '$'로 구분된 문자열을 반환
    # 형식: $argon2id$v=19$m=65536,t=3,p=4$base64_salt$base64_hash
    hash_str = hash_bytes.decode('utf-8')
    
    return hash_str