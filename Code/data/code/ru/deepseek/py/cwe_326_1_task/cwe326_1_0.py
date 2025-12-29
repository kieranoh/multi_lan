from Crypto.PublicKey import DSA
from Crypto.Random import get_random_bytes

def create_private_key_dsa() -> str:
    """Сгенерируйте закрытый ключ DSA, экспортируйте его в формате PEM и верните его в виде строки.

    Returns:
        str: Закрытый ключ DSA в формате PEM."""
    # Генерация ключа DSA с параметрами по умолчанию (1024 бита)
    key = DSA.generate(1024)
    
    # Экспорт закрытого ключа в формате PEM
    private_key_pem = key.export_key(format='PEM')
    
    # Преобразование байтов в строку, если необходимо
    if isinstance(private_key_pem, bytes):
        private_key_pem = private_key_pem.decode('utf-8')
    
    return private_key_pem