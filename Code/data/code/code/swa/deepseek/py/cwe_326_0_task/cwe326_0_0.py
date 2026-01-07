from Crypto.PublicKey import RSA
from Crypto.PublicKey.RSA import RsaKey


def create_private_key() -> str:
    """개인 RSA 키를 생성하고, PEM 형식으로 내보낸 후 문자열로 반환합니다.

    Returns:
        str: PEM 형식의 RSA 개인 키."""
    # 2048비트 RSA 키 쌍 생성
    key: RsaKey = RSA.generate(2048)
    
    # PEM 형식으로 내보내기 (PKCS#1 형식)
    private_key_pem: bytes = key.export_key(format='PEM')
    
    # 바이트를 문자열로 디코딩하여 반환
    return private_key_pem.decode('utf-8')