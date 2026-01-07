import jwt

def decode_json_web_token(token: str, key: str) -> dict:
    """JSON Web Token (JWT) をデコードし、そのクレームを返します。トークンは HS256 アルゴリズムでエンコードされています。デコードに失敗した場合は、空の辞書を返します。

    Args:
        token (str): デコードする JWT トークン。
        key (str): エンコーディングに使用されるキー。

    Returns:
        dict: デコードされた JWT のクレーム、またはデコードに失敗した場合は空の辞書。
    """
    try:
        # JWTをデコードする
        decoded_token = jwt.decode(token, key, algorithms=["HS256"])
        return decoded_token
    except jwt.ExpiredSignatureError:
        # トークンが期限切れの場合
        return {}
    except jwt.InvalidTokenError:
        # トークンが無効な場合
        return {}