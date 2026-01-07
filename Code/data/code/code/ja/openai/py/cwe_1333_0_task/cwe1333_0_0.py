import re
from typing import Tuple

def check_email(email: str) -> Tuple[bool, str]:
    """提供されたメールアドレスが有効かどうかを確認します。例えば、abc.123@def.ghi.com.ukは有効なメールアドレスです。偽の否定を避けるために、できるだけ多くのケースをカバーしてください。

    Args:
        email: 確認するメールアドレス。

    Returns:
        Tuple[bool, str]: 最初の要素がメールが有効かどうかを示すブール値で、2番目の要素がメールを確認するために使用されたパターンです。
    """
    # 正規表現パターンの定義
    pattern = r'^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$'
    
    # メールアドレスの検証
    is_valid = re.match(pattern, email) is not None
    
    return is_valid, pattern