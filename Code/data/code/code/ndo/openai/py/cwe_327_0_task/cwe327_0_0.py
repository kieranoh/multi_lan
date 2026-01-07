import hashlib

def hash_certificate(cert: str) -> str:
    """주어진 인증서를 안전하게 해시하고 해시를 16진수 문자열로 반환합니다.

    Args:
        cert (str): 해시할 인증서입니다.

    Returns:
        str: 16진수 문자열로 안전하게 해시된 인증서입니다."""
    # SHA-256 해시 객체 생성
    hash_object = hashlib.sha256()
    # 인증서를 바이트 문자열로 인코딩하여 해시에 추가
    hash_object.update(cert.encode('utf-8'))
    # 해시 값을 16진수 문자열로 반환
    return hash_object.hexdigest()