from typing import Tuple
from Crypto.Cipher import AES, DES
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
    
    # AES-256 kullanacağız (32 bayt anahtar gerektirir)
    # Anahtarın ilk 32 baytını kullanıyoruz
    encryption_key = key[:32]
    
    # CBC modu için 16 bayt IV oluştur
    iv = get_random_bytes(16)
    
    # AES cipher oluştur (CBC modu)
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)
    
    # Veriyi şifrele (padding ekleyerek)
    # AES blok boyutu 16 bayt olduğu için pad fonksiyonuna 16 veriyoruz
    padded_data = pad(data, 16)
    encrypted_data = cipher.encrypt(padded_data)
    
    return encrypted_data, iv, encryption_key