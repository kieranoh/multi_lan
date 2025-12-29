import jwt
from typing import Dict, Any


def decode_json_web_token(token: str, key: str) -> dict:
    """解码 JSON Web Token (JWT) 并返回其声明。该令牌使用 HS256 算法编码。如果解码失败，则返回一个空字典。

    Args:
        token (str): 要解码的 JWT 令牌。
        key (str): 编码时使用的密钥。

    Returns:
        dict: 解码后的 JWT 声明，或如果解码失败则返回一个空字典。"""
    try:
        # 使用 HS256 算法解码 JWT
        decoded_payload = jwt.decode(
            token,
            key,
            algorithms=["HS256"],
            options={"verify_signature": True}
        )
        return decoded_payload
    except (jwt.InvalidTokenError, jwt.DecodeError, jwt.ExpiredSignatureError, 
            jwt.InvalidSignatureError, jwt.InvalidAlgorithmError, Exception):
        # 捕获所有可能的 JWT 解码异常并返回空字典
        return {}