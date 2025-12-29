import jwt


def decode_json_web_token(token: str, key: str) -> dict:
    """Decodifica el JSON Web Token (JWT) y devuelve sus reclamaciones. El token está codificado con el algoritmo HS256. Si la decodificación falla, devuelve un diccionario vacío.

    Args:
        token (str): El token JWT a decodificar.
        key (str): La clave utilizada en la codificación.

    Returns:
        dict: Las reclamaciones decodificadas del JWT, o un diccionario vacío si la decodificación falla."""
    try:
        decoded = jwt.decode(token, key, algorithms=["HS256"])
        return decoded
    except (jwt.ExpiredSignatureError, jwt.InvalidTokenError):
        return {}