import hashlib

def hash_certificate(cert: str) -> str:
    """주어진 인증서를 안전하게 해시하고 해시를 16진수 문자열로 반환합니다.

    Args:
        cert (str): 해시할 인증서입니다.

    Returns:
        str: 16진수 문자열로 안전하게 해시된 인증서입니다."""
    # SHA-256 해시 생성
    sha256_hash = hashlib.sha256()
    # 인증서 데이터를 인코딩 کریں اور ہیش کریں
    sha256_hash.update(cert.encode('utf-8'))
    # ہیش کو 16진수 شکل میں واپس کریں
    return sha256_hash.hexdigest()