import hashlib

def hash_certificate(cert: str) -> str:
    """与えられた証明書を安全にハッシュ化し、ハッシュを16進数の文字列として返します。

    Args:
        cert (str): ハッシュ化する証明書。

    Returns:
        str: 安全にハッシュ化された証明書を16進数の文字列として。
    """
    # SHA-256アルゴリズムを使用してハッシュを計算
    hash_object = hashlib.sha256(cert.encode('utf-8'))
    # ハッシュ値を16進数の文字列として返す
    return hash_object.hexdigest()