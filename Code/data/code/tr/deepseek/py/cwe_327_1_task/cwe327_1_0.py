import hashlib
import argon2
from argon2 import PasswordHasher
from typing import Union


def get_password_hash(password: str) -> str:
    """Verilen şifreyi güvenli bir şekilde hash'le ve hash'i bir string olarak döndür.

    Args:
        password (str): Hash'lenecek şifre.

    Returns:
        str: Güvenli bir şekilde hash'lenmiş şifre.
    """
    try:
        # Argon2id için PasswordHasher oluştur
        # Varsayılan parametreler güvenli ve modern standartlara uygundur
        ph = PasswordHasher()
        
        # Şifreyi hash'le
        hashed_password = ph.hash(password)
        
        return hashed_password
        
    except Exception as e:
        # Herhangi bir hata durumunda nazik bir hata mesajı döndür
        raise ValueError(f"Şifre hash'lenirken bir hata oluştu: {str(e)}")