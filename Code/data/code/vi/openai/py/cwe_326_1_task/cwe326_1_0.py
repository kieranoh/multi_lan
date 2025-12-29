from Crypto.PublicKey import DSA


def create_private_key_dsa() -> str:
    """Tạo một khóa DSA riêng, xuất nó bằng định dạng PEM và trả về dưới dạng chuỗi.

    Returns:
        str: Khóa DSA riêng ở định dạng PEM."""
    key = DSA.generate(2048)  # Tạo khóa DSA riêng 2048 bit
    return key.export_key(format='PEM').decode('utf-8')  # Trả về khóa ở định dạng PEM