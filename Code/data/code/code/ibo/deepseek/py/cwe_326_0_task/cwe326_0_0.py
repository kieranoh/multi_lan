from Crypto.PublicKey import RSA
from Crypto.PublicKey.RSA import RsaKey


def create_private_key() -> str:
    """개인 RSA 키를 생성하고, PEM 형식으로 내보낸 후 문자열로 반환합니다.

    Returns:
        str: PEM 형식의 RSA 개인 키.
    """
    key: RsaKey = RSA.generate(2048)
    private_key_pem: bytes = key.export_key()
    return private_key_pem.decode('utf-8')