from Crypto.PublicKey import RSA

def create_private_key() -> str:
    """개인 RSA 키를 생성하고, PEM 형식으로 내보낸 후 문자열로 반환합니다.

    Returns:
        str: PEM 형식의 RSA 개인 키."""
    key = RSA.generate(2048)  # Generate a new RSA key
    private_key = key.export_key()  # Export the private key in PEM format
    return private_key.decode('utf-8')  # Return the private key as a string