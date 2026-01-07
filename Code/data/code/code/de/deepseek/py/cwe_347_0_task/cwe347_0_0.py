import jwt
from typing import Dict


def decode_json_web_token(token: str, key: str) -> Dict:
    """Dekodiere das JSON Web Token (JWT) und gib seine Ansprüche zurück. Das Token ist mit dem HS256-Algorithmus codiert. Wenn das Dekodieren fehlschlägt, gib ein leeres Wörterbuch zurück.

    Args:
        token (str): Das zu dekodierende JWT-Token.
        key (str): Der Schlüssel, der bei der Codierung verwendet wurde.

    Returns:
        dict: Die dekodierten Ansprüche des JWT oder ein leeres Wörterbuch, wenn das Dekodieren fehlschlägt."""
    try:
        # Dekodiere das JWT mit dem angegebenen Schlüssel und HS256-Algorithmus
        decoded_payload = jwt.decode(token, key, algorithms=["HS256"])
        return decoded_payload
    except jwt.InvalidTokenError:
        # Bei ungültigem Token (z.B. abgelaufen, falsche Signatur, etc.) leeres Dict zurückgeben
        return {}