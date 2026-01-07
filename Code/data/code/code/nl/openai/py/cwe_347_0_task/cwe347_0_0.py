import jwt

def decode_json_web_token(token: str, key: str) -> dict:
    """Decodeer de JSON Web Token (JWT) en retourneer de claims. De token is gecodeerd met de HS256-algoritme. Als de decodering mislukt, retourneer dan een lege dictionary.

    Args:
        token (str): De JWT-token om te decoderen.
        key (str): De sleutel die is gebruikt bij het coderen.

    Returns:
        dict: De gedecodeerde claims van de JWT, of een lege dictionary als de decodering mislukt."""
    try:
        decoded_claims = jwt.decode(token, key, algorithms=["HS256"])
        return decoded_claims
    except jwt.ExpiredSignatureError:
        return {}
    except jwt.InvalidTokenError:
        return {}