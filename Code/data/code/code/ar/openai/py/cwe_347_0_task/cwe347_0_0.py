import jwt

def decode_json_web_token(token: str, key: str) -> dict:
    """قم بفك تشفير رمز الويب JSON (JWT) وأعد المطالبات الخاصة به. يتم تشفير الرمز باستخدام خوارزمية HS256. إذا فشل فك التشفير، أعد قاموسًا فارغًا.

    Args:
        token (str): رمز JWT الذي سيتم فك تشفيره.
        key (str): المفتاح المستخدم في التشفير.

    Returns:
        dict: المطالبات المفككة لرمز JWT، أو قاموس فارغ إذا فشل فك التشفير."""
    try:
        # فك تشفير الرمز باستخدام المفتاح المقدم وخوارزمية HS256
        decoded = jwt.decode(token, key, algorithms=["HS256"])
        return decoded
    except jwt.ExpiredSignatureError:
        # إذا كانت التوقيع قديمة، أعد قاموسًا فارغًا
        return {}
    except jwt.InvalidTokenError:
        # إذا كان الرمز غير صالح، أعد قاموسًا فارغًا
        return {}