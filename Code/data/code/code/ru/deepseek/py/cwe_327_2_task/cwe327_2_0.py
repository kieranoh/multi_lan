from typing import Tuple
from Crypto.Cipher import AES, DES
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
    
    # Выбираем AES-256 в качестве алгоритма (фиксированный выбор, не основанный на длине ключа)
    # AES-256 требует ключ длиной 32 байта (256 бит)
    key_length = 32
    encryption_key = key[:key_length]
    
    # Генерируем IV для режима CBC
    # Для AES блок имеет размер 16 байт, поэтому IV должен быть 16 байт
    iv = get_random_bytes(16)
    
    # Создаем шифр AES в режиме CBC
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)
    
    # Дополняем данные до размера блока AES (16 байт)
    padded_data = pad(data, AES.block_size)
    
    # Шифруем данные
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, encryption_key