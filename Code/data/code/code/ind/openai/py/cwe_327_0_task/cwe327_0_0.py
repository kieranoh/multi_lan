import hashlib


def hash_certificate(cert: str) -> str:
    """주어진 인증서를 안전하게 해시하고 해시를 16진수 문자열로 반환합니다.

    Args:
        cert (str): 해시할 인증서입니다.

    Returns:
        str: 16진수 문자열로 안전하게 해시된 인증서입니다."""
    # SHA-256 해시 객체 생성
    sha256 = hashlib.sha256()
    # 인증서 문자열을 바이트로 인코딩하여 해시 업데이트
    sha256.update(cert.encode('utf-8'))
    # 16진수 문자열로 해시 반환
    return sha256.hexdigest()