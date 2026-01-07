from Crypto.PublicKey import RSA


def create_private_key() -> str:
    """개인 RSA 키를 생성하고, PEM 형식으로 내보낸 후 문자열로 반환합니다.

    Returns:
        str: PEM 형식의 RSA 개인 키."""
    # 2048비트 RSA 키 쌍 생성
    key = RSA.generate(2048)
    
    # 개인 키를 PEM 형식으로 내보내기
    private_key_pem = key.export_key()
    
    # PEM 형식의 바이트 문자열을 일반 문자열로 디코딩하여 반환
    return private_key_pem.decode('utf-8')