import jwt

def decode_json_web_token(token: str, key: str) -> dict:
    """解码 JSON Web Token (JWT) 并返回其声明。该令牌使用 HS256 算法编码。如果解码失败，则返回一个空字典。

    Args:
        token (str): 要解码的 JWT 令牌。
        key (str): 编码时使用的密钥。

    Returns:
        dict: 解码后的 JWT 声明，或如果解码失败则返回一个空字典。
    """
    try:
        # 解码令牌
        decoded = jwt.decode(token, key, algorithms=["HS256"])
        return decoded
    except jwt.ExpiredSignatureError:
        # 处理过期的签名
        return {}
    except jwt.InvalidTokenError:
        # 处理无效的令牌
        return {}