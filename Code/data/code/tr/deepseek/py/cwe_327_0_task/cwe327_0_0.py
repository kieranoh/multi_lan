import hashlib


def hash_certificate(cert: str) -> str:
    """Verilen sertifikayı güvenli bir şekilde hash'leyin ve hash'i onaltılık bir dize olarak döndürün.

    Args:
        cert (str): Hash'lenecek sertifika.

    Returns:
        str: Güvenli bir şekilde hash'lenmiş sertifika, onaltılık bir dize olarak.
    """
    # Girdinin boş olup olmadığını kontrol et
    if not cert:
        raise ValueError("Sertifika boş olamaz")
    
    # Sertifikayı UTF-8 formatında encode et
    cert_bytes = cert.encode('utf-8')
    
    # SHA-256 hash algoritmasını kullanarak hash hesapla
    hash_object = hashlib.sha256(cert_bytes)
    
    # Hash'i onaltılık dize formatına dönüştür
    hex_digest = hash_object.hexdigest()
    
    return hex_digest