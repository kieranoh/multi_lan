from Crypto.PublicKey import DSA
from Crypto.Random import get_random_bytes


def create_private_key_dsa() -> str:
    """プライベートDSAキーを生成し、PEM形式でエクスポートして文字列として返します。

    Returns:
        str: PEM形式のDSAプライベートキー。"""
    # 2048ビットのDSAキーを生成
    key = DSA.generate(2048)
    
    # PEM形式でエクスポート
    private_key_pem = key.export_key(format='PEM')
    
    # バイト列を文字列にデコードして返す
    return private_key_pem.decode('utf-8')