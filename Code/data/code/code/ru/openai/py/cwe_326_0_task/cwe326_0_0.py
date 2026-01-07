from Crypto.PublicKey import RSA

def create_private_key() -> str:
    """Сгенерируйте закрытый ключ RSA, экспортируйте его в формате PEM и верните его в виде строки.

    Returns:
        str: Закрытый ключ RSA в формате PEM."""
    key = RSA.generate(2048)  # Генерация закрытого ключа RSA длиной 2048 бит
    private_key = key.export_key()  # Экспорт ключа в формате PEM
    return private_key.decode('utf-8')  # Возврат ключа в виде строки