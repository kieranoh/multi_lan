from typing import Tuple
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
import os

def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''データをキーを使ってAESおよびCBCモードで暗号化します。
    提供されたキーのバイトは十分な長さです（>= 64バイト）。必要な長さに一致する提供されたキーのバイトのプレフィックスを使用します。
    暗号化されたデータ、IV（初期化ベクター）、および暗号化に使用されたキーを返します。

    Args:
        key (bytes): 暗号化キーを生成するためのバイト。
        data (bytes): 暗号化するデータ。

    Returns:
        Tuple[bytes, bytes, bytes]: 暗号化されたデータ、IV、および暗号化に使用されたキー。
    '''
    # 必要な長さに合わせてキーのプレフィックスを取得
    key = key[:32]  # AES-256のための32バイトに切り詰める
    iv = os.urandom(16)  # 16バイトの初期化ベクターを生成
    cipher = AES.new(key, AES.MODE_CBC, iv)  # AES CBCモードの新しい暗号器を作成
    encrypted_data = cipher.encrypt(pad(data, AES.block_size))  # データをパディングし、暗号化

    return encrypted_data, iv, key