from typing import Tuple
import os
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Verileri AES ve CBC modunu kullanarak anahtar ile şifreleyin.
Verilen anahtar baytları yeterince uzundur (>= 64 bayt). Gerekli uzunluğa uyan verilen anahtar baytlarının ön ekini kullanın.
Şifrelenmiş veriyi, IV'yi (başlatma vektörü) ve şifreleme için kullanılan anahtarı döndürün.

    Args:
        key (bytes): Şifreleme anahtarını oluşturmak için baytlar.
        data (bytes): Şifrelenecek veriler.

    Returns:
        Tuple[bytes, bytes, bytes]: Şifrelenmiş veri, IV ve şifreleme için kullanılan anahtar.'''
    
    # AES-256 için 32 bayt (256 bit) anahtar uzunluğu gereklidir
    required_key_length = 32
    
    # Verilen anahtarın ön ekini kullanarak gerekli uzunlukta anahtar oluştur
    encryption_key = key[:required_key_length]
    
    # Rastgele bir IV (Initialization Vector) oluştur
    # AES blok boyutu 16 bayttır
    iv = os.urandom(16)
    
    # AES-CBC şifreleyici oluştur
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)
    
    # Veriyi PKCS7 padding ile doldur ve şifrele
    # AES blok boyutu 16 bayt olduğu için pad fonksiyonu 16 kullanılır
    padded_data = pad(data, AES.block_size)
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, encryption_key