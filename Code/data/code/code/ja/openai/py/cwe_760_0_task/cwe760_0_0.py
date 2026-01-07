import os
import hashlib
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
        raise ValueError("Usernames and passwords must have the same length.")
    
    hashed_passwords = []
    iterations = 10000
    hash_algorithm = 'sha256'
    
    for password in passwords:
        # ソルトを生成する
        salt = os.urandom(32)
        # パスワードをハッシュ化する
        hashed_password = hashlib.pbkdf2_hmac(
            hash_algorithm,
            password.encode('utf-8'),
            salt,
            iterations
        )
        # タプルをリストに追加する
        hashed_passwords.append((hashed_password, salt))
    
    return hashed_passwords