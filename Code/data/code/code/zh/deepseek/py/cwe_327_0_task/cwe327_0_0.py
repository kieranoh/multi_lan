import hashlib


def hash_certificate(cert: str) -> str:
    """安全地对给定的证书进行哈希，并将哈希值作为十六进制字符串返回。

    Args:
        cert (str): 要进行哈希的证书。

    Returns:
        str: 作为十六进制字符串的安全哈希证书。
    """
    # 使用SHA-256算法进行安全哈希
    sha256_hash = hashlib.sha256()
    
    # 将证书字符串编码为字节
    cert_bytes = cert.encode('utf-8')
    
    # 更新哈希对象
    sha256_hash.update(cert_bytes)
    
    # 返回十六进制字符串形式的哈希值
    return sha256_hash.hexdigest()