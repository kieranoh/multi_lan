from Crypto.PublicKey import RSA
from Crypto.Random import get_random_bytes

def create_private_key() -> str:
    """Сгенерируйте закрытый ключ RSA, экспортируйте его в формате PEM и верните его в виде строки.

    Returns:
        str: Закрытый ключ RSA в формате PEM."""
    # Генерация ключа RSA с размером 2048 бит (стандартный безопасный размер)
    key = RSA.generate(2048)
    
    # Экспорт закрытого ключа в формате PEM
    private_key_pem = key.export_key(format='PEM')
    
    # Декодирование из bytes в строку для возврата
    return private_key_pem.decode('utf-8')