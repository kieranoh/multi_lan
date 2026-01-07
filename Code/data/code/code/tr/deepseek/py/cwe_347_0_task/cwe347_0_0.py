import jwt
from typing import Dict, Any


def decode_json_web_token(token: str, key: str) -> dict:
    """JSON Web Token'ı (JWT) çöz ve iddialarını döndür. Token, HS256 algoritması ile kodlanmıştır. Çözme işlemi başarısız olursa, boş bir sözlük döndür."""
    try:
        # HS256 algoritması ile token'ı çöz
        decoded_payload = jwt.decode(
            token,
            key,
            algorithms=["HS256"],
            options={"verify_signature": True}
        )
        return decoded_payload
    except jwt.InvalidTokenError:
        # Geçersiz token durumunda boş sözlük döndür
        return {}
    except Exception:
        # Diğer tüm hatalar için de boş sözlük döndür
        return {}