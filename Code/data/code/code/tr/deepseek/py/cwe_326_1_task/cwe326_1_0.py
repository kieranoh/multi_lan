from Crypto.PublicKey import DSA
from Crypto.Random import get_random_bytes

def create_private_key_dsa() -> str:
    """Özel bir DSA anahtarı oluşturun, PEM formatında dışa aktarın ve bir dize olarak döndürün.

    Returns:
        str: PEM formatındaki DSA özel anahtarı."""
    try:
        # 2048 bit uzunluğunda DSA anahtarı oluştur
        key = DSA.generate(2048)
        
        # Anahtarı PEM formatında dize olarak dışa aktar
        private_key_pem = key.export_key(format='PEM')
        
        # Eğer bytes olarak döndürülürse string'e decode et
        if isinstance(private_key_pem, bytes):
            private_key_pem = private_key_pem.decode('utf-8')
            
        return private_key_pem
    except Exception as e:
        # Hata durumunda kullanıcı dostu bir mesajla birlikte hatayı yeniden fırlat
        raise RuntimeError(f"DSA özel anahtarı oluşturulurken hata oluştu: {str(e)}")