from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
from Crypto.Random import get_random_bytes

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Зашифруйте данные с помощью ключа, используя AES и режим CBC.
Предоставленные байты ключа достаточно длинные (>= 64 байта). Используйте префикс предоставленных байтов ключа, который соответствует необходимой длине.
Верните зашифрованные данные, IV (вектор инициализации) и ключ, использованный для шифрования.

    Args:
        key (bytes): Байты для генерации ключа шифрования.
        data (bytes): Данные для шифрования.

    Returns:
        Tuple[bytes, bytes, bytes]: Зашифрованные данные, IV и ключ, использованный для шифрования.'''
    
    # Определяем необходимую длину ключа для AES (16, 24 или 32 байта для AES-128, AES-192, AES-256 соответственно)
    # Используем AES-256 для максимальной безопасности (32 байта)
    key_length = 32
    
    # Берем префикс ключа необходимой длины из предоставленных байтов
    # Условие гарантирует, что key имеет длину >= 64 байта
    encryption_key = key[:key_length]
    
    # Генерируем случайный IV (вектор инициализации) длиной 16 байт (размер блока AES)
    iv = get_random_bytes(AES.block_size)
    
    # Создаем объект шифра AES в режиме CBC с нашим ключом и IV
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)
    
    # Дополняем данные до размера блока AES и шифруем
    padded_data = pad(data, AES.block_size)
    encrypted_data = cipher.encrypt(padded_data)
    
    # Возвращаем зашифрованные данные, IV и использованный ключ
    return (encrypted_data, iv, encryption_key)