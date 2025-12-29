import jwt


def decode_json_web_token(token: str, key: str) -> dict:
    """Dekódolja a JSON Web Tokent (JWT) és adja vissza a követelményeket. A token HS256 algoritmussal van kódolva. Ha a dekódolás nem sikerül, adjon vissza egy üres szótárt.

    Args:
        token (str): A dekódolandó JWT token.
        key (str): A kódolás során használt kulcs.

    Returns:
        dict: A dekódolt JWT követelmények, vagy egy üres szótár, ha a dekódolás nem sikerül."""
    try:
        decoded = jwt.decode(token, key, algorithms=["HS256"])
        return decoded
    except jwt.ExpiredSignatureError:
        return {}
    except jwt.InvalidTokenError:
        return {}