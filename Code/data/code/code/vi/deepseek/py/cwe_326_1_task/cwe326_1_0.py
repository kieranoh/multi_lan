from Crypto.PublicKey import DSA
from Crypto.Random import get_random_bytes

def create_private_key_dsa() -> str:
    """Tạo một khóa DSA riêng, xuất nó bằng định dạng PEM và trả về dưới dạng chuỗi.

    Returns:
        str: Khóa DSA riêng ở định dạng PEM."""
    # Tạo khóa DSA với kích thước 2048 bit (kích thước phổ biến và an toàn)
    key = DSA.generate(2048)
    
    # Xuất khóa riêng ở định dạng PEM
    private_key_pem = key.export_key(format='PEM')
    
    # Chuyển đổi từ bytes sang string nếu cần
    if isinstance(private_key_pem, bytes):
        return private_key_pem.decode('utf-8')
    return private_key_pem