import jwt

def decode_json_web_token(token: str, key: str) -> dict:
    """Dekodiere das JSON Web Token (JWT) und gib seine Ansprüche zurück. Das Token ist mit dem HS256-Algorithmus codiert. Wenn das Dekodieren fehlschlägt, gib ein leeres Wörterbuch zurück.

    Args:
        token (str): Das zu dekodierende JWT-Token.
        key (str): Der Schlüssel, der bei der Codierung verwendet wurde.

    Returns:
        dict: Die dekodierten Ansprüche des JWT oder ein leeres Wörterbuch, wenn das Dekodieren fehlschlägt."""
    try:
        decoded = jwt.decode(token, key, algorithms=["HS256"])
        return decoded
    except jwt.ExpiredSignatureError:
        return {}
    except jwt.InvalidTokenError:
        return {}