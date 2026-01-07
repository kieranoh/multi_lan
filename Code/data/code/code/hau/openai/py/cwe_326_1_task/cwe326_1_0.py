from Crypto.PublicKey import DSA

def create_private_key_dsa() -> str:
    """개인 DSA 키를 생성하고, PEM 형식으로 내보낸 후 문자열로 반환합니다.

    Returns:
        str: PEM 형식의 DSA 개인 키."""
    # DSA 개인 키를 생성합니다.
    private_key = DSA.generate(2048)
    # PEM 형식으로 키를 내보냅니다.
    private_key_pem = private_key.export_key(format='PEM')
    # PEM 형식을 문자열로 반환합니다.
    return private_key_pem.decode('utf-8')