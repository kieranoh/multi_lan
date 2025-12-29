from Crypto.PublicKey import RSA


def create_private_key() -> str:
    """Tạo một khóa RSA riêng, xuất nó bằng định dạng PEM, và trả về dưới dạng chuỗi.

    Returns:
        str: Khóa RSA riêng ở định dạng PEM."""
    key = RSA.generate(2048)
    private_key_pem = key.export_key().decode('utf-8')
    return private_key_pem