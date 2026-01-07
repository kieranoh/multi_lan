import jwt

def decode_json_web_token(token: str, key: str) -> dict:
    """Dekoda JSON Web Token (JWT) och returnera dess påståenden. Token är kodad med HS256-algoritmen. Om dekodningen misslyckas, returnera en tom ordbok.

    Args:
        token (str): JWT-tokenen som ska dekodas.
        key (str): Nyckeln som användes vid kodning.

    Returns:
        dict: De dekodade påståendena av JWT, eller en tom ordbok om dekodningen misslyckas."""
    try:
        decoded = jwt.decode(token, key, algorithms=["HS256"])
        return decoded
    except jwt.ExpiredSignatureError:
        return {}
    except jwt.InvalidTokenError:
        return {}