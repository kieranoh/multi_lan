from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
from Crypto.Random import get_random_bytes

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Verileri AES ve CBC modunu kullanarak anahtar ile şifreleyin.
    Verilen anahtar baytları yeterince uzundur (>= 64 bayt). Gerekli uzunluğa uyan verilen anahtar baytlarının ön ekini kullanın.
    Şifrelenmiş veriyi, IV'yi (başlatma vektörü) ve şifreleme için kullanılan anahtarı döndürün.
    
    Args:
        key (bytes): Şifreleme anahtarını oluşturmak için baytlar.
        data (bytes): Şifrelenecek veriler.
    
    Returns:
        Tuple[bytes, bytes, bytes]: Şifrelenmiş veri, IV ve şifreleme için kullanılan anahtar.'''
    
    # Anahtarı 32 bayta kısalt
    truncated_key = key[:32]  # AES-256 için 32 baytlık anahtar
    # Başlatma vektörünü oluştur
    iv = get_random_bytes(AES.block_size)
    # Şifreleme işlemi
    cipher = AES.new(truncated_key, AES.MODE_CBC, iv)
    encrypted_data = cipher.encrypt(pad(data, AES.block_size))
    
    return encrypted_data, iv, truncated_key