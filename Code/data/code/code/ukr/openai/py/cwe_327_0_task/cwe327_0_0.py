import hashlib

def hash_certificate(cert: str) -> str:
    """주어진 인증서를 안전하게 해시하고 해시를 16진수 문자열로 반환합니다.

    Args:
        cert (str): 해시할 인증서입니다.

    Returns:
        str: 16진수 문자열로 안전하게 해시된 인증서입니다."""
    # Create a SHA-256 hash object
    sha256 = hashlib.sha256()
    
    # Update the hash object with the bytes of the certificate
    sha256.update(cert.encode('utf-8'))
    
    # Return the hexadecimal digest of the hash
    return sha256.hexdigest()