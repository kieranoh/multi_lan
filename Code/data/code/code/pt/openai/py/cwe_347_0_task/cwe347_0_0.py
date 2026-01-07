import jwt

def decode_json_web_token(token: str, key: str) -> dict:
    """Decodifique o JSON Web Token (JWT) e retorne suas reivindicações. O token é codificado com o algoritmo HS256. Se a decodificação falhar, retorne um dicionário vazio.

    Args:
        token (str): O token JWT a ser decodificado.
        key (str): A chave usada na codificação.

    Returns:
        dict: As reivindicações decodificadas do JWT, ou um dicionário vazio se a decodificação falhar."""
    try:
        return jwt.decode(token, key, algorithms=["HS256"])
    except jwt.ExpiredSignatureError:
        return {}
    except jwt.InvalidTokenError:
        return {}