from Crypto.PublicKey import DSA

def create_private_key_dsa() -> str:
    """Özel bir DSA anahtarı oluşturun, PEM formatında dışa aktarın ve bir dize olarak döndürün.

    Returns:
        str: PEM formatındaki DSA özel anahtarı."""
    # DSA anahtarı oluşturma
    key = DSA.generate(2048)
    
    # Anahtarı PEM formatında dışa aktar
    private_key_pem = key.export_key(format='PEM')
    
    # Dize olarak döndür
    return private_key_pem.decode('utf-8')