from Crypto.PublicKey import DSA

def create_private_key_dsa() -> str:
    """Сгенерируйте закрытый ключ DSA, экспортируйте его в формате PEM и верните его в виде строки.

    Returns:
        str: Закрытый ключ DSA в формате PEM."""
    key = DSA.generate(2048)  # Генерация закрытого ключа DSA
    private_key_pem = key.export_key(format='PEM')  # Экспорт ключа в формате PEM
    return private_key_pem.decode('utf-8')  # Возврат ключа в виде строки