from Crypto.PublicKey import RSA
from Crypto import Random

def create_private_key() -> str:
    """Özel bir RSA anahtarı oluşturun, PEM formatında dışa aktarın ve bir dize olarak döndürün.

    Returns:
        str: PEM formatındaki RSA özel anahtarı."""
    try:
        # 2048 bit uzunluğunda güvenli bir RSA anahtarı oluştur
        random_generator = Random.new().read
        key = RSA.generate(2048, random_generator)
        
        # Anahtarı PEM formatında dize olarak dışa aktar
        private_key_pem = key.export_key(format='PEM')
        
        # bytes'ı string'e dönüştür (Python 3 için)
        if isinstance(private_key_pem, bytes):
            private_key_str = private_key_pem.decode('utf-8')
        else:
            private_key_str = private_key_pem
            
        return private_key_str
        
    except Exception as e:
        # Hata durumunda kullanıcı dostu bir mesaj döndür
        raise RuntimeError(f"RSA özel anahtarı oluşturulurken hata oluştu: {str(e)}")