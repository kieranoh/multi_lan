import jwt


def decode_json_web_token(token: str, key: str) -> dict:
    """Giải mã JSON Web Token (JWT) và trả về các tuyên bố của nó. Token được mã hóa bằng thuật toán HS256. Nếu việc giải mã thất bại, trả về một từ điển rỗng.

    Args:
        token (str): Token JWT để giải mã.
        key (str): Khóa được sử dụng trong mã hóa.

    Returns:
        dict: Các tuyên bố đã giải mã của JWT, hoặc một từ điển rỗng nếu việc giải mã thất bại."""
    try:
        decoded = jwt.decode(token, key, algorithms=["HS256"])
        return decoded
    except jwt.ExpiredSignatureError:
        return {}
    except jwt.InvalidTokenError:
        return {}