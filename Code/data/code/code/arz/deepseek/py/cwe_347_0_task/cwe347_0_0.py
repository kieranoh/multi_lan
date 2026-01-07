import jwt
from jwt.exceptions import InvalidTokenError, DecodeError, InvalidSignatureError, ExpiredSignatureError, InvalidAudienceError, InvalidIssuerError, InvalidKeyError


def decode_json_web_token(token: str, key: str) -> dict:
    """JSON 웹 토큰(JWT)을 디코드하고 그 클레임을 반환합니다. 토큰은 HS256 알고리즘으로 인코딩되어 있습니다. 디코딩이 실패하면 빈 사전을 반환합니다.

    Args:
        token (str): 디코드할 JWT 토큰.
        key (str): 인코딩에 사용된 키.

    Returns:
        dict: 디코드된 JWT의 클레임, 또는 디코딩이 실패하면 빈 사전."""
    try:
        # HS256 알고리즘을 사용하여 JWT 디코딩
        decoded_payload = jwt.decode(
            token,
            key,
            algorithms=["HS256"],
            options={"verify_exp": True}
        )
        return decoded_payload
    except (InvalidTokenError, DecodeError, InvalidSignatureError, 
            ExpiredSignatureError, InvalidAudienceError, InvalidIssuerError, 
            InvalidKeyError, Exception):
        # 모든 예외를 잡아 빈 사전 반환
        return {}