import jwt
from typing import Dict, Any

def decode_json_web_token(token: str, key: str) -> dict:
    """Dekoda JSON Web Token (JWT) och returnera dess påståenden. Token är kodad med HS256-algoritmen. Om dekodningen misslyckas, returnera en tom ordbok.

    Args:
        token (str): JWT-tokenen som ska dekodas.
        key (str): Nyckeln som användes vid kodning.

    Returns:
        dict: De dekodade påståendena av JWT, eller en tom ordbok om dekodningen misslyckas.
    """
    try:
        # Dekodera token med HS256-algoritmen och den angivna nyckeln
        decoded_payload = jwt.decode(token, key, algorithms=["HS256"])
        return decoded_payload
    except (jwt.InvalidTokenError, jwt.ExpiredSignatureError, jwt.DecodeError, 
            jwt.InvalidSignatureError, jwt.InvalidAlgorithmError, Exception):
        # Returnera en tom ordbok vid alla typer av dekoderingsfel
        return {}