import jwt


def decode_json_web_token(token: str, key: str) -> dict:
    """Dekódujte JSON Web Token (JWT) a vraťte jeho nároky. Token je zakódován pomocí algoritmu HS256. Pokud dekódování selže, vraťte prázdný slovník.

    Args:
        token (str): JWT token k dekódování.
        key (str): Klíč použitý při kódování.

    Returns:
        dict: Dekódované nároky JWT, nebo prázdný slovník, pokud dekódování selže."""
    try:
        # Dekódování tokenu pomocí HS256 algoritmu s ověřením podpisu
        decoded_payload = jwt.decode(token, key, algorithms=["HS256"])
        return decoded_payload
    except jwt.exceptions.InvalidTokenError:
        # Zachycení všech chyb souvisejících s neplatným tokenem
        return {}
    except Exception:
        # Obecná výjimka pro jakékoli jiné chyby
        return {}