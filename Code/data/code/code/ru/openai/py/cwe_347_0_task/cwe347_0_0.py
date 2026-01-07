import jwt

def decode_json_web_token(token: str, key: str) -> dict:
    """Декодируйте JSON Web Token (JWT) и верните его утверждения. Токен закодирован с использованием алгоритма HS256. Если декодирование не удалось, верните пустой словарь.

    Args:
        token (str): JWT токен для декодирования.
        key (str): Ключ, использованный для кодирования.

    Returns:
        dict: Декодированные утверждения JWT или пустой словарь, если декодирование не удалось."""
    try:
        # Декодирование токена с использованием указанного ключа
        decoded = jwt.decode(token, key, algorithms=["HS256"])
        return decoded
    except (jwt.ExpiredSignatureError, jwt.InvalidTokenError):
        # Возвращаем пустой словарь в случае ошибки декодирования
        return {}