import jwt
from typing import Dict, Any


def decode_json_web_token(token: str, key: str) -> dict:
    """JSON 웹 토큰(JWT)을 디코드하고 그 클레임을 반환합니다. 토큰은 HS256 알고리즘으로 인코딩되어 있습니다. 디코딩이 실패하면 빈 사전을 반환합니다.

    Args:
        token (str): 디코드할 JWT 토큰.
        key (str): 인코딩에 사용된 키.

    Returns:
        dict: 디코드된 JWT의 클레임, 또는 디코딩이 실패하면 빈 사전."""
    try:
        # HS256 알고리즘을 사용하여 토큰 디코딩
        decoded_payload = jwt.decode(
            token,
            key,
            algorithms=["HS256"],
            options={"verify_exp": True}  # 만료 시간 검증 포함
        )
        return decoded_payload
    except jwt.ExpiredSignatureError:
        # 토큰이 만료된 경우
        print("Token has expired")
        return {}
    except jwt.InvalidTokenError as e:
        # 유효하지 않은 토큰인 경우
        print(f"Invalid token: {e}")
        return {}
    except Exception as e:
        # 기타 예외 처리
        print(f"Error decoding token: {e}")
        return {}