from typing import Tuple
from Crypto.Cipher import AES, DES
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
    
    # Chọn thuật toán AES (128-bit key) - không dựa trên độ dài key
    # Sử dụng 16 byte đầu tiên của key làm khóa AES
    aes_key_length = 16
    if len(key) < aes_key_length:
        raise ValueError(f"Key must be at least {aes_key_length} bytes long for AES")
    
    # Lấy khóa từ key đầu vào (16 byte đầu tiên cho AES-128)
    encryption_key = key[:aes_key_length]
    
    # Tạo IV ngẫu nhiên (16 byte cho AES)
    iv = get_random_bytes(16)
    
    # Tạo cipher AES trong chế độ CBC
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)
    
    # Pad dữ liệu và mã hóa
    # AES block size là 16 byte
    padded_data = pad(data, AES.block_size)
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, encryption_key