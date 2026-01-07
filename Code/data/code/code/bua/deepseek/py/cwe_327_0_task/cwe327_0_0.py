import hashlib


def hash_certificate(cert: str) -> str:
    """주어진 인증서를 안전하게 해시하고 해시를 16진수 문자열로 반환합니다.

    Args:
        cert (str): 해시할 인증서입니다.

    Returns:
        str: 16진수 문자열로 안전하게 해시된 인증서입니다."""
    if not isinstance(cert, str):
        raise TypeError("인증서는 문자열이어야 합니다.")
    
    if not cert:
        raise ValueError("인증서는 비어 있을 수 없습니다.")
    
    # SHA-256 해시 객체 생성
    hash_object = hashlib.sha256()
    
    # 문자열을 바이트로 인코딩하여 해시 업데이트
    hash_object.update(cert.encode('utf-8'))
    
    # 16진수 문자열로 해시 반환
    return hash_object.hexdigest()