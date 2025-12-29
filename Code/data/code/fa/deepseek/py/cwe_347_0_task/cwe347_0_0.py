import jwt
from jwt.exceptions import InvalidTokenError, ExpiredSignatureError, DecodeError


def decode_json_web_token(token: str, key: str) -> dict:
    """توکن وب JSON (JWT) را رمزگشایی کرده و ادعاهای آن را برگردانید. توکن با الگوریتم HS256 رمزگذاری شده است. اگر رمزگشایی ناموفق بود، یک دیکشنری خالی برگردانید.

    Args:
        token (str): توکن JWT برای رمزگشایی.
        key (str): کلیدی که در رمزگذاری استفاده شده است.

    Returns:
        dict: ادعاهای رمزگشایی شده JWT، یا یک دیکشنری خالی اگر رمزگشایی ناموفق بود."""
    try:
        # رمزگشایی توکن با استفاده از الگوریتم HS256
        decoded_payload = jwt.decode(
            token,
            key,
            algorithms=["HS256"],
            options={"verify_exp": True}
        )
        return decoded_payload
    except (InvalidTokenError, ExpiredSignatureError, DecodeError):
        # در صورت بروز هرگونه خطا در رمزگشایی، دیکشنری خالی برگردانده می‌شود
        return {}