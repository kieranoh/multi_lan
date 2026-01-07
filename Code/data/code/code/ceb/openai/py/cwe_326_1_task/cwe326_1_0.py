from Crypto.PublicKey import DSA

def create_private_key_dsa() -> str:
    """개인 DSA 키를 생성하고, PEM 형식으로 내보낸 후 문자열로 반환합니다.

    Returns:
        str: PEM 형식의 DSA 개인 키."""
    private_key = DSA.generate(2048)  # 2048 bit DSA key
    pem = private_key.export_key(format='PEM')
    return pem.decode('utf-8')