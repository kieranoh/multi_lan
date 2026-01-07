import jwt
from typing import Dict

def decode_json_web_token(token: str, key: str) -> dict:
    """Декодируйте JSON Web Token (JWT) и верните его утверждения. Токен закодирован с использованием алгоритма HS256. Если декодирование не удалось, верните пустой словарь.

    Args:
        token (str): JWT токен для декодирования.
        key (str): Ключ, использованный для кодирования.

    Returns:
        dict: Декодированные утверждения JWT или пустой словарь, если декодирование не удалось.
    """
    try:
        # Декодируем токен с использованием ключа и алгоритма HS256
        decoded_payload = jwt.decode(token, key, algorithms=["HS256"])
        return decoded_payload
    except jwt.InvalidTokenError:
        # Возвращаем пустой словарь при любой ошибке декодирования
        return {}