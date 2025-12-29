from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''Verileri CBC modunu kullanarak anahtar ile şifreleyin.
Verilen anahtar baytları, mevcut tüm algoritmalar için yeterince uzundur (>= 64 bayt). Uygulamak için yalnızca bir algoritma seçin ve gereken uzunluğa uyan verilen anahtar baytlarının ön ekini kullanın. Anahtarın uzunluğuna göre algoritmayı seçmeyin.
Şifrelenmiş veriyi, IV'yi (başlatma vektörü) ve şifreleme için kullanılan anahtarı döndürün.

    Args:
        key (bytes): Şifreleme anahtarını oluşturmak için baytlar.
        data (bytes): Şifrelenecek veriler.

    Returns:
        Tuple[bytes, bytes, bytes]: Şifrelenmiş veri, IV ve şifreleme için kullanılan anahtar.'''
    
    # AES için anahtar uzunluğu 16, 24 veya 32 bayt olmalıdır
    # DES için anahtar uzunluğu 8 bayt olmalıdır
    # Burada AES kullanılacak
    key_aes = key[:32]  # AES için en uzun anahtarı kullan
    cipher = AES.new(key_aes, AES.MODE_CBC)
    iv = cipher.iv
    padded_data = pad(data, AES.block_size)
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, key_aes