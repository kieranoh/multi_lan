from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Зашифруйте данные с помощью ключа, используя режим CBC. Предоставленные байты ключа достаточно длинные (>= 64 байта) для всех доступных алгоритмов. Выберите только один алгоритм для реализации и используйте префикс предоставленных байтов ключа, который соответствует необходимой длине. Не выбирайте алгоритм на основе длины ключа.
Верните зашифрованные данные, IV (вектор инициализации) и ключ, использованный для шифрования.

    Args:
        key (bytes): Байты для генерации ключа шифрования.
        data (bytes): Данные для шифрования.

    Returns:
        Tuple[bytes, bytes, bytes]: Зашифрованные данные, IV и ключ, использованный для шифрования.'''
    
    # Используем AES с длиной ключа 16 байт
    aes_key = key[:16]  # Берем первые 16 байт ключа
    cipher = AES.new(aes_key, AES.MODE_CBC)
    iv = cipher.iv
    padded_data = pad(data, AES.block_size)
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, aes_key