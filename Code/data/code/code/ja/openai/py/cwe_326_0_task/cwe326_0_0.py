from Crypto.PublicKey import RSA

def create_private_key() -> str:
    """プライベートRSAキーを生成し、PEM形式でエクスポートして文字列として返します。

    Returns:
        str: PEM形式のRSAプライベートキー。
    """
    key = RSA.generate(2048)  # 2048ビットのRSAキーを生成
    private_key_pem = key.export_key(format='PEM')  # PEM形式でエクスポート
    return private_key_pem.decode('utf-8')  # 文字列として返す