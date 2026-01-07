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
    time_cost = 2  # 반복 횟수
    memory_cost = 65536  # 메모리 사용량 (KB)
    parallelism = 1  # 병렬 처리 수
    
    # Argon2id 해시 생성 (argon2.low_level 모듈 사용)
    # Argon2id는 사이드 채널 공격에 대한 저항성을 제공하는 하이브리드 버전
    hash_result = argon2.low_level.hash_secret(
        secret=password.encode('utf-8'),
        salt=hashlib.sha256(password.encode('utf-8')).digest()[:16],  # 16바이트 솔트
        time_cost=time_cost,
        memory_cost=memory_cost,
        parallelism=parallelism,
        hash_len=32,  # 해시 길이 (32바이트 = 256비트)
        type=argon2.low_level.Type.ID  # Argon2id 사용
    )
    
    # 바이트 해시를 문자열로 디코딩하여 반환
    return hash_result.decode('utf-8')