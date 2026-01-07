import jwt
from jwt.exceptions import InvalidTokenError, ExpiredSignatureError, InvalidSignatureError, DecodeError


def decode_json_web_token(token: str, key: str) -> dict:
    """Dekodirajte JSON Web Token (JWT) i vratite njegove tvrdnje. Token je kodiran s HS256 algoritmom. Ako dekodiranje ne uspije, vratite prazan rječnik.

    Args:
        token (str): JWT token za dekodiranje.
        key (str): Ključ korišten u kodiranju.

    Returns:
        dict: Dekodirane tvrdnje JWT-a, ili prazan rječnik ako dekodiranje ne uspije."""
    try:
        # Dekodiranje tokena s HS256 algoritmom
        decoded_payload = jwt.decode(
            token,
            key,
            algorithms=["HS256"],
            options={"verify_exp": True}
        )
        return decoded_payload
    except (InvalidTokenError, ExpiredSignatureError, InvalidSignatureError, DecodeError):
        # Vraćanje praznog rječnika za sve greške dekodiranja
        return {}