from Crypto.PublicKey import DSA
from Crypto.Random import get_random_bytes

def create_private_key_dsa() -> str:
    """개인 DSA 키를 생성하고, PEM 형식으로 내보낸 후 문자열로 반환합니다.

    Returns:
        str: PEM 형식의 DSA 개인 키."""
    # DSA 키 생성 (기본적으로 1024비트)
    key = DSA.generate(1024)
    
    # PEM 형식으로 내보내기
    private_key_pem = key.export_key(format='PEM')
    
    # bytes를 문자열로 디코딩하여 반환
    return private_key_pem.decode('utf-8')