import jwt

def decode_json_web_token(token: str, key: str) -> dict:
    """Zdekoduj token JSON Web Token (JWT) i zwróć jego roszczenia. Token jest zakodowany algorytmem HS256. Jeśli dekodowanie się nie powiedzie, zwróć pusty słownik.

    Args:
        token (str): Token JWT do zdekodowania.
        key (str): Klucz użyty do kodowania.

    Returns:
        dict: Zdekodowane roszczenia JWT lub pusty słownik, jeśli dekodowanie się nie powiedzie."""
    try:
        # Dekodowanie tokena JWT
        decoded = jwt.decode(token, key, algorithms=['HS256'])
        return decoded
    except (jwt.ExpiredSignatureError, jwt.InvalidTokenError):
        # Zwracanie pustego słownika w przypadku błędu dekodowania
        return {}