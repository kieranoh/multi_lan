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
    
    # SHA-256 해시 생성
    sha256_hash = hashlib.sha256(cert.encode('utf-8'))
    
    # 16진수 문자열로 반환
    return sha256_hash.hexdigest()