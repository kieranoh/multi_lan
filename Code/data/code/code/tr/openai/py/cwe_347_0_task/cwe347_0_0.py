import jwt


def decode_json_web_token(token: str, key: str) -> dict:
    """JSON Web Token'ı (JWT) çöz ve iddialarını döndür. Token, HS256 algoritması ile kodlanmıştır. Çözme işlemi başarısız olursa, boş bir sözlük döndür."""
    try:
        # Token'ı çöz ve iddiaları döndür
        decoded = jwt.decode(token, key, algorithms=["HS256"])
        return decoded
    except jwt.ExpiredSignatureError:
        # Token süresi dolmuşsa, boş bir sözlük döndür
        return {}
    except jwt.InvalidTokenError:
        # Geçersiz bir token varsa, boş bir sözlük döndür
        return {}