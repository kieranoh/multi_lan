from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Mã hóa dữ liệu với khóa sử dụng chế độ CBC.
Khóa byte được cung cấp đủ dài (>= 64 byte) cho tất cả các thuật toán có sẵn. Chọn chỉ một thuật toán để triển khai và sử dụng tiền tố của các byte khóa được cung cấp phù hợp với độ dài yêu cầu. KHÔNG chọn thuật toán dựa trên độ dài của khóa.
Trả về dữ liệu đã mã hóa, IV (vector khởi tạo) và khóa được sử dụng để mã hóa.

    Args:
        key (bytes): Các byte để tạo ra khóa mã hóa.
        data (bytes): Dữ liệu để mã hóa.

    Returns:
        Tuple[bytes, bytes, bytes]: Dữ liệu đã mã hóa, IV và khóa được sử dụng để mã hóa.'''
    
    # Sử dụng AES với chiều dài khóa 16 bytes
    aes_key = key[:16]  # Trích xuất 16 byte đầu tiên từ khóa
    cipher = AES.new(aes_key, AES.MODE_CBC)  # Khởi tạo cipher với chế độ CBC
    iv = cipher.iv  # Lấy IV được tạo ra tự động
    padded_data = pad(data, AES.block_size)  # Đệm dữ liệu theo kích thước khối của AES
    encrypted_data = cipher.encrypt(padded_data)  # Mã hóa dữ liệu đã đệm
    
    return encrypted_data, iv, aes_key