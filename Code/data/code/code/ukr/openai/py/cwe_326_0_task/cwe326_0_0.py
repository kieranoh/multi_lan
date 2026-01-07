from Crypto.PublicKey import RSA

def create_private_key() -> str:
    """개인 RSA 키를 생성하고, PEM 형식으로 내보낸 후 문자열로 반환합니다.

    Returns:
        str: PEM 형식의 RSA 개인 키."""
    private_key = RSA.generate(2048)
    pem_key = private_key.export_key()
    return pem_key.decode('utf-8')