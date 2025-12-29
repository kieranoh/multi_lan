import jwt
from typing import Dict, Any

def decode_json_web_token(token: str, key: str) -> dict:
    """قم بفك تشفير رمز الويب JSON (JWT) وأعد المطالبات الخاصة به. يتم تشفير الرمز باستخدام خوارزمية HS256. إذا فشل فك التشفير، أعد قاموسًا فارغًا.

    Args:
        token (str): رمز JWT الذي سيتم فك تشفيره.
        key (str): المفتاح المستخدم في التشفير.

    Returns:
        dict: المطالبات المفككة لرمز JWT، أو قاموس فارغ إذا فشل فك التشفير."""
    try:
        # فك تشفير الرمز باستخدام خوارزمية HS256
        decoded_payload = jwt.decode(
            token,
            key,
            algorithms=["HS256"],
            options={"verify_signature": True}
        )
        return decoded_payload
    except jwt.InvalidTokenError:
        # في حالة أي خطأ في فك التشفير (توقيع غير صالح، رمز منتهي الصلاحية، إلخ)
        return {}
    except Exception:
        # معالجة أي استثناءات أخرى
        return {}