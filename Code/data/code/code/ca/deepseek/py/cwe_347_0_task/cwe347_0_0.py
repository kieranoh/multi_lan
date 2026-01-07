import jwt


def decode_json_web_token(token: str, key: str) -> dict:
    """Decodifica el JSON Web Token (JWT) i retorna les seves reclamacions. El token està codificat amb l'algorisme HS256. Si la decodificació falla, retorna un diccionari buit.

    Args:
        token (str): El token JWT a decodificar.
        key (str): La clau utilitzada en la codificació.

    Returns:
        dict: Les reclamacions decodificades del JWT, o un diccionari buit si la decodificació falla."""
    try:
        # Decodificar el token utilitzant la clau i l'algorisme HS256
        claims = jwt.decode(token, key, algorithms=["HS256"])
        return claims
    except jwt.InvalidTokenError:
        # Retornar diccionari buit en cas de qualsevol error de decodificació
        return {}