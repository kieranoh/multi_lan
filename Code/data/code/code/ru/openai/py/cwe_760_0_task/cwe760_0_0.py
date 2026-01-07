import os
import hashlib
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
    
    result = []
    for password in passwords:
        salt = os.urandom(32)  # Генерация соли длиной 32 байта
        hashed_password = hashlib.pbkdf2_hmac(
            'sha256', 
            password.encode(),  # Кодируем пароль в байты
            salt, 
            10000  # Количество итераций
        )
        result.append((hashed_password, salt))
    
    return result