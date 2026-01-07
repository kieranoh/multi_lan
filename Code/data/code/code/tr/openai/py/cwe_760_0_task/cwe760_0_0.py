import os
import hashlib
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
    
    hashed_passwords = []
    for username, password in zip(usernames, passwords):
        # Salt oluştur
        salt = os.urandom(32)  # 32 bytelık bir tuz
        # Hashle
        hashed_password = hashlib.pbkdf2_hmac(
            'sha256',  # Hash algoritması
            password.encode('utf-8'),  # Şifreyi byte dizisine çevir
            salt,  # Tuz
            10000  # İterasyon sayısı
        )
        # Hashlenmiş şifre ve tuzu tuple olarak sakla
        hashed_passwords.append((hashed_password, salt))
    
    return hashed_passwords