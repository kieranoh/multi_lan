import jwt
from jwt.exceptions import InvalidTokenError, DecodeError, InvalidSignatureError, ExpiredSignatureError, InvalidAudienceError, InvalidIssuerError, InvalidAlgorithmError


def decode_json_web_token(token: str, key: str) -> dict:
    """Décodez le JSON Web Token (JWT) et renvoyez ses revendications. Le jeton est encodé avec l'algorithme HS256. Si le décodage échoue, renvoyez un dictionnaire vide.

    Args:
        token (str): Le jeton JWT à décoder.
        key (str): La clé utilisée pour l'encodage.

    Returns:
        dict: Les revendications décodées du JWT, ou un dictionnaire vide si le décodage échoue.
    """
    try:
        # Décoder le token avec la clé et l'algorithme HS256
        decoded_payload = jwt.decode(
            token,
            key,
            algorithms=["HS256"],
            options={"verify_signature": True}
        )
        return decoded_payload
    except (InvalidTokenError, DecodeError, InvalidSignatureError, 
            ExpiredSignatureError, InvalidAudienceError, InvalidIssuerError,
            InvalidAlgorithmError, Exception):
        # Retourner un dictionnaire vide en cas d'échec du décodage
        return {}