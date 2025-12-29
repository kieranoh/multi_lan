from Crypto.PublicKey import RSA
from Crypto.Random import get_random_bytes


def create_private_key() -> str:
    """プライベートRSAキーを生成し、PEM形式でエクスポートして文字列として返します。

    Returns:
        str: PEM形式のRSAプライベートキー。"""
    # 2048ビットのRSAキーペアを生成
    key = RSA.generate(2048)
    
    # プライベートキーをPEM形式でエクスポート
    private_key_pem = key.export_key(format='PEM')
    
    # バイト列を文字列にデコードして返す
    return private_key_pem.decode('utf-8')