import jwt

def decode_json_web_token(token: str, key: str) -> dict:
    """Dekodirajte JSON Web Token (JWT) i vratite njegove tvrdnje. Token je kodiran s HS256 algoritmom. Ako dekodiranje ne uspije, vratite prazan rječnik.

    Args:
        token (str): JWT token za dekodiranje.
        key (str): Ključ korišten u kodiranju.

    Returns:
        dict: Dekodirane tvrdnje JWT-a, ili prazan rječnik ako dekodiranje ne uspije."""
    try:
        # Dekodiranje JWT-a koristeći zadani ključ i specifičnu metodu (HS256)
        decoded = jwt.decode(token, key, algorithms=["HS256"])
        return decoded
    except jwt.ExpiredSignatureError:
        # Ako je potpis istekao, vraćamo prazan rječnik
        return {}
    except jwt.InvalidTokenError:
        # Ako je token nevažeći, također vraćamo prazan rječnik
        return {}