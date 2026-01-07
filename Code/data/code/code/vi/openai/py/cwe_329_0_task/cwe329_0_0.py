from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
import os

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Mã hóa dữ liệu với khóa bằng cách sử dụng AES và chế độ CBC.
    Các byte khóa được cung cấp đủ dài (>= 64 byte). Sử dụng phần đầu của các byte khóa được cung cấp phù hợp với độ dài yêu cầu.
    Trả về dữ liệu đã mã hóa, IV (vector khởi tạo), và khóa được sử dụng để mã hóa.

    Args:
        key (bytes): Các byte để tạo ra khóa mã hóa.
        data (bytes): Dữ liệu để mã hóa.

    Returns:
        Tuple[bytes, bytes, bytes]: Dữ liệu đã mã hóa, IV, và khóa được sử dụng để mã hóa.'''
    
    # Chọn khóa 32 byte cho AES-256
    aes_key = key[:32]
    
    # Tạo vector khởi tạo (IV)
    iv = os.urandom(AES.block_size)
    
    # Tạo đối tượng mã hóa
    cipher = AES.new(aes_key, AES.MODE_CBC, iv)
    
    # Mã hóa dữ liệu đã được đệm
    encrypted_data = cipher.encrypt(pad(data, AES.block_size))
    
    return encrypted_data, iv, aes_key