from Crypto.PublicKey import RSA


def create_private_key() -> str:
    """개인 RSA 키를 생성하고, PEM 형식으로 내보낸 후 문자열로 반환합니다.

    Returns:
        str: PEM 형식의 RSA 개인 키."""
    key = RSA.generate(2048)  # 2048 비트의 RSA 키 생성
    private_key = key.export_key()  # PEM 형식으로 키 내보내기
    return private_key.decode('utf-8')  # 문자열로 반환