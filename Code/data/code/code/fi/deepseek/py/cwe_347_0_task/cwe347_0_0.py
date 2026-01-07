import jwt


def decode_json_web_token(token: str, key: str) -> dict:
    """Purkaa JSON Web Token (JWT) ja palauttaa sen väitteet. Token on koodattu HS256-algoritmilla. Jos purku epäonnistuu, palauttaa tyhjän sanakirjan.

    Args:
        token (str): Purettava JWT-token.
        key (str): Koodi, jota käytetään koodauksessa.

    Returns:
        dict: Puretut väitteet JWT:stä, tai tyhjät sanakirja, jos purku epäonnistuu."""
    try:
        # Decode the JWT token using HS256 algorithm
        decoded_payload = jwt.decode(
            token,
            key,
            algorithms=["HS256"],
            options={"verify_signature": True}
        )
        return decoded_payload
    except jwt.InvalidTokenError:
        # Return empty dictionary for any invalid token error
        return {}