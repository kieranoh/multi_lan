import jwt


def decode_json_web_token(token: str, key: str) -> dict:
    """JSON 웹 토큰(JWT)을 디코드하고 그 클레임을 반환합니다. 토큰은 HS256 알고리즘으로 인코딩되어 있습니다. 디코딩이 실패하면 빈 사전을 반환합니다.

    Args:
        token (str): 디코드할 JWT 토큰.
        key (str): 인코딩에 사용된 키.

    Returns:
        dict: 디코드된 JWT의 클레임, 또는 디코딩이 실패하면 빈 사전."""
    try:
        # jwt.decode()를 사용하여 토큰 디코딩
        # verify=True가 기본값이므로 서명 검증이 수행됨
        decoded_payload = jwt.decode(
            token,
            key,
            algorithms=["HS256"],
            options={"verify_signature": True}
        )
        return decoded_payload
    except jwt.InvalidTokenError:
        # 모든 유효하지 않은 토큰 예외에 대해 빈 사전 반환
        return {}