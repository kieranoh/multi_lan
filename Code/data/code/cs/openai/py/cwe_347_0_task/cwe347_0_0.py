import jwt

def decode_json_web_token(token: str, key: str) -> dict:
    """Dekódujte JSON Web Token (JWT) a vraťte jeho nároky. Token je zakódován pomocí algoritmu HS256. Pokud dekódování selže, vraťte prázdný slovník.

    Args:
        token (str): JWT token k dekódování.
        key (str): Klíč použitý při kódování.

    Returns:
        dict: Dekódované nároky JWT, nebo prázdný slovník, pokud dekódování selže."""
    try:
        return jwt.decode(token, key, algorithms=["HS256"])
    except jwt.ExpiredSignatureError:
        return {}
    except jwt.InvalidTokenError:
        return {}