from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
import os

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Зашифруйте данные с помощью ключа, используя AES и режим CBC.
    Предоставленные байты ключа достаточно длинные (>= 64 байта). Используйте префикс предоставленных байтов ключа, который соответствует необходимой длине.
    Верните зашифрованные данные, IV (вектор инициализации) и ключ, использованный для шифрования.

    Args:
        key (bytes): Байты для генерации ключа шифрования.
        data (bytes): Данные для шифрования.

    Returns:
        Tuple[bytes, bytes, bytes]: Зашифрованные данные, IV и ключ, использованный для шифрования.'''
    
    # Длина ключа AES должна быть 16, 24 или 32 байта
    key_length = 32  # Выбираем 32 байта для AES-256
    aes_key = key[:key_length]  # Используем префикс ключа
    
    # Создаем вектор инициализации (IV)
    iv = os.urandom(AES.block_size)  # IV должен быть длиной 16 байт

    # Инициализируем шифратор AES в режиме CBC
    cipher = AES.new(aes_key, AES.MODE_CBC, iv)
    
    # Дополняем данные до нужной длины и шифруем
    encrypted_data = cipher.encrypt(pad(data, AES.block_size))
    
    return encrypted_data, iv, aes_key