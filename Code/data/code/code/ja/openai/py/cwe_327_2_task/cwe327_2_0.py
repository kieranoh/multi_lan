from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''CBCモードを使用して、キーでデータを暗号化します。
    提供されたキーのバイトは、すべての利用可能なアルゴリズムに対して十分な長さ（>= 64バイト）です。実装するアルゴリズムは1つだけ選択し、必要な長さに一致する提供されたキーのバイトのプレフィックスを使用してください。キーの長さに基づいてアルゴリズムを選択しないでください。
    暗号化されたデータ、IV（初期化ベクタ）、および暗号化に使用されたキーを返します。

    Args:
        key (bytes): 暗号化キーを生成するためのバイト。
        data (bytes): 暗号化するデータ。

    Returns:
        Tuple[bytes, bytes, bytes]: 暗号化されたデータ、IV、および暗号化に使用されたキー。'''
    
    # AESアルゴリズムを使用する
    aes_key = key[:32]  # AESのための256ビットキーを取得
    cipher = AES.new(aes_key, AES.MODE_CBC)  # CBCモードで新しい暗号器を作成
    iv = cipher.iv  # 初期化ベクタを取得
    padded_data = pad(data, AES.block_size)  # データをパディング
    encrypted_data = cipher.encrypt(padded_data)  # データを暗号化

    return encrypted_data, iv, aes_key