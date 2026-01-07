import hashlib
import os
from typing import List, Tuple


def hash_passwords(
    usernames: List[str], passwords: List[str]
) -> List[Tuple[bytes, bytes]]:
    '''ユーザーのパスワードのリストが与えられた場合、hashlib.pbkdf2_hmacを使用してSHA-256でハッシュ化し、出力ハッシュと同じ長さのソルトを使用し、10000回の反復を行います。ハッシュ化されたパスワードとハッシュ化に使用されたソルトを返し、データベースに保存します。

    Args:
        usernames: ユーザー名のリスト。
        passwords: ハッシュ化するユーザーのパスワードのリスト。

    Returns:
        List[Tuple[bytes, bytes]]: ハッシュ化されたパスワードとハッシュ化に使用されたソルトを含むタプルのリスト。'''
    
    if len(usernames) != len(passwords):
        raise ValueError("usernamesとpasswordsのリストの長さが一致しません")
    
    result = []
    
    for username, password in zip(usernames, passwords):
        # パスワードをバイト列に変換
        password_bytes = password.encode('utf-8')
        
        # ソルトを生成 (SHA-256の出力長は32バイト)
        salt = os.urandom(32)
        
        # PBKDF2-HMAC-SHA256でパスワードをハッシュ化
        hashed_password = hashlib.pbkdf2_hmac(
            'sha256',
            password_bytes,
            salt,
            10000
        )
        
        result.append((hashed_password, salt))
    
    return result