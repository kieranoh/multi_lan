import jwt

def decode_json_web_token(token: str, key: str) -> dict:
    """Decodifica il JSON Web Token (JWT) e restituisci le sue affermazioni. Il token è codificato con l'algoritmo HS256. Se la decodifica fallisce, restituisci un dizionario vuoto.

    Args:
        token (str): Il token JWT da decodificare.
        key (str): La chiave utilizzata nella codifica.

    Returns:
        dict: Le affermazioni decodificate del JWT, o un dizionario vuoto se la decodifica fallisce."""
    try:
        return jwt.decode(token, key, algorithms=["HS256"])
    except jwt.ExpiredSignatureError:
        return {}
    except jwt.InvalidTokenError:
        return {}