import jwt
from jwt.exceptions import InvalidTokenError, DecodeError, InvalidSignatureError, ExpiredSignatureError, InvalidAudienceError, InvalidIssuerError, InvalidIssuedAtError, ImmatureSignatureError


def decode_json_web_token(token: str, key: str) -> dict:
    """JSON Web Token (JWT) をデコードし、そのクレームを返します。トークンは HS256 アルゴリズムでエンコードされています。デコードに失敗した場合は、空の辞書を返します。

    Args:
        token (str): デコードする JWT トークン。
        key (str): エンコーディングに使用されるキー。

    Returns:
        dict: デコードされた JWT のクレーム、またはデコードに失敗した場合は空の辞書。
    """
    try:
        # HS256アルゴリズムを使用してトークンをデコード
        decoded_payload = jwt.decode(
            token,
            key,
            algorithms=["HS256"],
            options={
                "verify_signature": True,
                "verify_exp": True,
                "verify_nbf": True,
                "verify_iat": True,
                "verify_aud": False,
                "verify_iss": False,
                "require_exp": False,
                "require_iat": False,
                "require_nbf": False
            }
        )
        return decoded_payload
    except (
        InvalidTokenError,
        DecodeError,
        InvalidSignatureError,
        ExpiredSignatureError,
        InvalidAudienceError,
        InvalidIssuerError,
        InvalidIssuedAtError,
        ImmatureSignatureError
    ):
        # デコードに失敗した場合は空の辞書を返す
        return {}