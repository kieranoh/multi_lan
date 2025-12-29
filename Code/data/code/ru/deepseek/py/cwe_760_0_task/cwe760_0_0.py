import hashlib
import os
from typing import List, Tuple


def hash_passwords(
    usernames: List[str], passwords: List[str]
) -> List[Tuple[bytes, bytes]]:
    '''Учитывая список паролей пользователей, используйте hashlib.pbkdf2_hmac для их хеширования с помощью SHA-256, соли такой же длины, как выходной хеш, и 10000 итераций. Верните хешированные пароли и соли, использованные для хеширования, для дальнейшего хранения в базе данных.

    Args:
        usernames: Список имен пользователей.
        passwords: Список паролей пользователей для хеширования.

    Returns:
        List[Tuple[bytes, bytes]]: Список кортежей, содержащих хешированные пароли и соли, использованные для хеширования.'''
    
    # Определяем длину хеша для SHA-256 (32 байта)
    hash_length = 32  # SHA-256 produces 32-byte hash
    
    result = []
    
    for username, password in zip(usernames, passwords):
        # Генерируем соль такой же длины, как выходной хеш
        salt = os.urandom(hash_length)
        
        # Хешируем пароль с помощью PBKDF2-HMAC-SHA256
        # Пароль должен быть преобразован в байты
        password_bytes = password.encode('utf-8')
        hashed_password = hashlib.pbkdf2_hmac(
            'sha256',
            password_bytes,
            salt,
            10000,  # количество итераций
            dklen=hash_length  # длина выходного ключа
        )
        
        result.append((hashed_password, salt))
    
    return result