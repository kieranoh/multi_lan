import jwt
from typing import Dict, Any

def decode_json_web_token(token: str, key: str) -> dict:
    """Dekodirajte JSON Web Token (JWT) i vratite njegove tvrdnje. Token je kodiran sa HS256 algoritmom. Ako dekodiranje ne uspe, vratite prazan rečnik.

    Args:
        token (str): JWT token koji treba dekodirati.
        key (str): Ključ korišćen u kodiranju.

    Returns:
        dict: Dekodirane tvrdnje JWT-a, ili prazan rečnik ako dekodiranje ne uspe."""
    try:
        # Dekodiranje JWT tokena sa HS256 algoritmom
        decoded_payload = jwt.decode(
            token,
            key,
            algorithms=["HS256"],
            options={"verify_exp": True}
        )
        return decoded_payload
    except jwt.ExpiredSignatureError:
        # Token je istekao
        return {}
    except jwt.InvalidTokenError:
        # Token je nevažeći iz bilo kog razloga
        return {}
    except Exception:
        # Hvatanje svih drugih izuzetaka za sigurnost
        return {}