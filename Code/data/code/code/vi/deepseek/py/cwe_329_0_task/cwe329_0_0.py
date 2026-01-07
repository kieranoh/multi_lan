from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
from Crypto.Random import get_random_bytes

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Mã hóa dữ liệu với khóa bằng cách sử dụng AES và chế độ CBC.
    Các byte khóa được cung cấp đủ dài (>= 64 byte). Sử dụng phần đầu của các byte khóa được cung cấp phù hợp với độ dài yêu cầu.
    Trả về dữ liệu đã mã hóa, IV (vector khởi tạo), và khóa được sử dụng để mã hóa.

    Args:
        key (bytes): Các byte để tạo ra khóa mã hóa.
        data (bytes): Dữ liệu để mã hóa.

    Returns:
        Tuple[bytes, bytes, bytes]: Dữ liệu đã mã hóa, IV, và khóa được sử dụng để mã hóa.'''
    
    # Xác định độ dài khóa AES (16, 24, hoặc 32 byte cho AES-128, AES-192, AES-256)
    # Sử dụng AES-256 (32 byte) để tăng cường bảo mật
    key_length = 32
    
    # Lấy phần đầu của key bytes với độ dài phù hợp
    # Đảm bảo key_bytes đủ dài
    if len(key) < key_length:
        raise ValueError(f"Key bytes phải có ít nhất {key_length} byte, nhưng chỉ có {len(key)} byte")
    
    encryption_key = key[:key_length]
    
    # Tạo IV ngẫu nhiên (16 byte cho AES block size)
    iv = get_random_bytes(AES.block_size)
    
    # Tạo cipher với chế độ CBC
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)
    
    # Pad dữ liệu và mã hóa
    padded_data = pad(data, AES.block_size)
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, encryption_key