import hashlib

def hash_certificate(cert: str) -> str:
    """安全地对给定的证书进行哈希，并将哈希值作为十六进制字符串返回。

    Args:
        cert (str): 要进行哈希的证书。

    Returns:
        str: 作为十六进制字符串的安全哈希证书。
    """
    # 使用SHA-256算法来生成证书的哈希值
    hash_object = hashlib.sha256(cert.encode())
    # 将哈希值转换为十六进制字符串
    hex_dig = hash_object.hexdigest()
    return hex_dig