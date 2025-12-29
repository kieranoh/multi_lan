import hashlib
import argon2
from typing import Optional


def get_password_hash(password: str) -> str:
    """与えられたパスワードを安全にハッシュ化し、ハッシュを文字列として返します。

    Args:
        password (str): ハッシュ化されるパスワード。

    Returns:
        str: 安全にハッシュ化されたパスワード。
    """
    # Argon2のパラメータ設定
    time_cost = 2          # 処理時間のコスト
    memory_cost = 65536    # メモリ使用量（KB単位）
    parallelism = 4        # 並列処理数
    hash_len = 32          # ハッシュ長（バイト）
    
    # Argon2idインスタンスの作成（デフォルトはArgon2id）
    argon2_hasher = argon2.PasswordHasher(
        time_cost=time_cost,
        memory_cost=memory_cost,
        parallelism=parallelism,
        hash_len=hash_len
    )
    
    # パスワードをハッシュ化
    hashed_password = argon2_hasher.hash(password)
    
    return hashed_password