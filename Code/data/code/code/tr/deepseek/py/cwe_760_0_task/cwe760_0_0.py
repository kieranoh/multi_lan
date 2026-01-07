import hashlib
import os
from typing import List, Tuple


def hash_passwords(
    usernames: List[str], passwords: List[str]
) -> List[Tuple[bytes, bytes]]:
    '''Kullanıcıların şifrelerinin bir listesini verin, bunları SHA-256 ile hashlemek için hashlib.pbkdf2_hmac kullanın, çıktı hash'inin uzunluğuna eşit tuzlar ve 10000 yineleme ile. Hashlenmiş şifreleri ve daha sonra bir veritabanında saklamak için kullanılan tuzları döndürün.

    Args:
        usernames: Bir kullanıcı adı listesi.
        passwords: Hashlenecek kullanıcıların şifrelerinin bir listesi.

    Returns:
        List[Tuple[bytes, bytes]]: Hashlenmiş şifreleri ve hashleme için kullanılan tuzları içeren bir tuple listesi.'''
    
    if len(usernames) != len(passwords):
        raise ValueError("Kullanıcı adları ve şifreler listeleri aynı uzunlukta olmalıdır.")
    
    result = []
    hash_length = 32  # SHA-256 için hash uzunluğu (32 byte = 256 bit)
    
    for username, password in zip(usernames, passwords):
        # Rastgele tuz oluştur (hash uzunluğu kadar)
        salt = os.urandom(hash_length)
        
        # Şifreyi hashle
        hashed_password = hashlib.pbkdf2_hmac(
            'sha256',
            password.encode('utf-8'),
            salt,
            10000,
            dklen=hash_length
        )
        
        result.append((hashed_password, salt))
    
    return result