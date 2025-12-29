import hashlib
import argon2
import secrets
import base64
import os

def get_password_hash(password: str) -> str:
    """Надежно захешируйте данный пароль и верните хеш в виде строки.

    Args:
        password (str): Пароль, который нужно захешировать.

    Returns:
        str: Надежно захешированный пароль."""
    
    # Генерация случайной соли для Argon2
    salt = secrets.token_bytes(16)
    
    # Создание хеша с использованием Argon2id (рекомендуемая версия)
    # Параметры настройки для баланса безопасности и производительности
    hasher = argon2.PasswordHasher(
        time_cost=3,      # Количество итераций
        memory_cost=65536, # Использование памяти в KiB (64 MiB)
        parallelism=4,    # Количество параллельных потоков
        hash_len=32,      # Длина хеша в байтах
        salt_len=16,      # Длина соли в байтах
        encoding='utf-8'  # Кодировка для строк
    )
    
    # Генерация хеша с использованием Argon2id
    # Argon2 автоматически добавляет соль и возвращает строку в формате,
    # который включает алгоритм, параметры, соль и хеш
    hash_result = hasher.hash(password)
    
    return hash_result