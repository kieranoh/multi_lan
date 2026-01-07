from typing import Tuple
from Crypto.Cipher import AES, DES
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
    # アルゴリズムの選択（キーの長さに基づかない固定選択）
    # AES-256を選択（32バイトのキーが必要）
    algorithm = "AES-256"
    key_length = 32  # AES-256のキー長
    
    # 提供されたキーから必要な長さのプレフィックスを使用
    encryption_key = key[:key_length]
    
    # IVの生成（AESのブロックサイズは16バイト）
    iv = get_random_bytes(16)
    
    # 暗号化の実行
    cipher = AES.new(encryption_key, AES.MODE_CBC, iv)
    encrypted_data = cipher.encrypt(pad(data, AES.block_size))
    
    return encrypted_data, iv, encryption_key