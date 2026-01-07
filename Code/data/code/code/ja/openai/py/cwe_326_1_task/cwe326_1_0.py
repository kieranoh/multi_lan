from Crypto.PublicKey import DSA

def create_private_key_dsa() -> str:
    """プライベートDSAキーを生成し、PEM形式でエクスポートして文字列として返します。

    Returns:
        str: PEM形式のDSAプライベートキー。
    """
    # DSAキーの生成
    key = DSA.generate(2048)
    # PEM形式でエクスポート
    private_key_pem = key.export_key(format='PEM')
    return private_key_pem.decode('utf-8')