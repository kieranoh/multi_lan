import jwt
from typing import Dict, Any


def decode_json_web_token(token: str, key: str) -> dict:
    """Decodifique o JSON Web Token (JWT) e retorne suas reivindicações. O token é codificado com o algoritmo HS256. Se a decodificação falhar, retorne um dicionário vazio.

    Args:
        token (str): O token JWT a ser decodificado.
        key (str): A chave usada na codificação.

    Returns:
        dict: As reivindicações decodificadas do JWT, ou um dicionário vazio se a decodificação falhar.
    """
    try:
        # Decodifica o token usando a chave fornecida e o algoritmo HS256
        claims = jwt.decode(token, key, algorithms=["HS256"])
        return claims
    except (jwt.InvalidTokenError, jwt.DecodeError, jwt.ExpiredSignatureError, 
            jwt.InvalidSignatureError, jwt.InvalidAlgorithmError, Exception):
        # Retorna um dicionário vazio para qualquer tipo de erro na decodificação
        return {}