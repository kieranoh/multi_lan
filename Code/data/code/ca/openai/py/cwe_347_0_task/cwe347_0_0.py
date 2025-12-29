import jwt

def decode_json_web_token(token: str, key: str) -> dict:
    """Decodifica el JSON Web Token (JWT) i retorna les seves reclamacions. El token està codificat amb l'algorisme HS256. Si la decodificació falla, retorna un diccionari buit.

    Args:
        token (str): El token JWT a decodificar.
        key (str): La clau utilitzada en la codificació.

    Returns:
        dict: Les reclamacions decodificades del JWT, o un diccionari buit si la decodificació falla."""
    try:
        # Decodificant el token JWT
        decoded = jwt.decode(token, key, algorithms=["HS256"])
        return decoded
    except jwt.InvalidTokenError:
        # Retornant un diccionari buit si la decodificació falla
        return {}