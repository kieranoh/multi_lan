from Crypto.PublicKey import RSA
from Crypto import Random

def create_private_key() -> str:
    """Tạo một khóa RSA riêng, xuất nó bằng định dạng PEM, và trả về dưới dạng chuỗi.

    Returns:
        str: Khóa RSA riêng ở định dạng PEM."""
    try:
        # Tạo bộ tạo số ngẫu nhiên an toàn
        random_generator = Random.new().read
        
        # Tạo cặp khóa RSA với độ dài 2048 bit (độ dài phổ biến và an toàn)
        key = RSA.generate(2048, random_generator)
        
        # Xuất khóa riêng ở định dạng PEM
        private_key_pem = key.export_key(format='PEM')
        
        # Chuyển từ bytes sang string để trả về
        return private_key_pem.decode('utf-8')
        
    except Exception as e:
        # Xử lý lỗi một cách duyên dáng
        raise RuntimeError(f"Không thể tạo khóa RSA: {str(e)}")