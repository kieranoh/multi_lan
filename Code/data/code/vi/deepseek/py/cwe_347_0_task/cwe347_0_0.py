import jwt
from typing import Dict, Any


def decode_json_web_token(token: str, key: str) -> Dict[str, Any]:
    """Giải mã JSON Web Token (JWT) và trả về các tuyên bố của nó. Token được mã hóa bằng thuật toán HS256. Nếu việc giải mã thất bại, trả về một từ điển rỗng.

    Args:
        token (str): Token JWT để giải mã.
        key (str): Khóa được sử dụng trong mã hóa.

    Returns:
        dict: Các tuyên bố đã giải mã của JWT, hoặc một từ điển rỗng nếu việc giải mã thất bại.
    """
    try:
        # Giải mã token với thuật toán HS256
        decoded_payload = jwt.decode(
            token,
            key,
            algorithms=["HS256"],
            options={"verify_exp": True}
        )
        return decoded_payload
    except jwt.InvalidTokenError:
        # Trả về từ điển rỗng cho tất cả các lỗi token không hợp lệ
        return {}