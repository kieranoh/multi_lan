import hashlib


def hash_certificate(cert: str) -> str:
    """与えられた証明書を安全にハッシュ化し、ハッシュを16進数の文字列として返します。

    Args:
        cert (str): ハッシュ化する証明書。

    Returns:
        str: 安全にハッシュ化された証明書を16進数の文字列として。"""
    if not isinstance(cert, str):
        raise TypeError("証明書は文字列でなければなりません")
    
    if not cert:
        raise ValueError("証明書は空であってはなりません")
    
    # SHA-256を使用して安全にハッシュ化
    hash_object = hashlib.sha256(cert.encode('utf-8'))
    hex_dig = hash_object.hexdigest()
    
    return hex_dig