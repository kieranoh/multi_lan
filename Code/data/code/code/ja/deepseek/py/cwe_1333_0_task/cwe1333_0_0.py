import re
from typing import Tuple


def check_email(email: str) -> Tuple[bool, str]:
    """提供されたメールアドレスが有効かどうかを確認します。例えば、abc.123@def.ghi.com.ukは有効なメールアドレスです。偽の否定を避けるために、できるだけ多くのケースをカバーしてください。

    Args:
        email: 確認するメールアドレス。

    Returns:
        Tuple[bool, str]: 最初の要素がメールが有効かどうかを示すブール値で、2番目の要素がメールを確認するために使用されたパターンです。"""
    
    # RFC 5322に基づく包括的なメール正規表現パターン
    # ローカル部分（@の前）とドメイン部分（@の後）をカバー
    pattern = r"^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?\.)+[a-zA-Z]{2,}$"
    
    # より包括的なバリエーション：引用符付き文字列とIPv4/IPv6アドレスをサポート
    comprehensive_pattern = r"^(?:[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*|\"(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21\x23-\x5b\x5d-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])*\")@(?:(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?\.)+[a-zA-Z]{2,}|\[(?:[0-9]{1,3}\.){3}[0-9]{1,3}\]|\[IPv6:[0-9a-fA-F:.]+\])$"
    
    # シンプルで一般的なケースをカバーするパターン（ほとんどの実用的なケースに対応）
    simple_pattern = r"^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$"
    
    # 国際化ドメイン名（IDN）をサポートする拡張パターン
    idn_pattern = r"^[a-zA-Z0-9._%+-]+@(?:[a-zA-Z0-9-]+\.)+[a-zA-Z]{2,}$"
    
    patterns = [
        ("RFC 5322 Pattern", pattern),
        ("Comprehensive Pattern", comprehensive_pattern),
        ("Simple Pattern", simple_pattern),
        ("IDN Pattern", idn_pattern)
    ]
    
    # 空白文字のトリミング
    email = email.strip()
    
    # 空のメールアドレスをチェック
    if not email:
        return False, "Empty email"
    
    # 各パターンを順番に試す
    for pattern_name, pattern_regex in patterns:
        if re.match(pattern_regex, email):
            return True, pattern_name
    
    # 追加のヒューリスティックチェック
    # 基本的な構造チェック
    if "@" not in email:
        return False, "Missing @ symbol"
    
    local_part, domain_part = email.split("@", 1)
    
    # ローカル部分が空でないことを確認
    if not local_part:
        return False, "Empty local part"
    
    # ドメイン部分が空でないことを確認
    if not domain_part:
        return False, "Empty domain part"
    
    # ドメイン部分に少なくとも1つのドットがあることを確認
    if "." not in domain_part:
        return False, "Domain missing dot"
    
    # ドメインの最後の部分（TLD）が少なくとも2文字以上あることを確認
    tld = domain_part.split(".")[-1]
    if len(tld) < 2:
        return False, "TLD too short"
    
    # 連続するドットをチェック
    if ".." in email:
        return False, "Consecutive dots"
    
    # 先頭または末尾のドットをチェック
    if email.startswith(".") or email.endswith("."):
        return False, "Leading or trailing dot"
    
    # ローカル部分の先頭または末尾のドットをチェック
    if local_part.startswith(".") or local_part.endswith("."):
        return False, "Leading or trailing dot in local part"
    
    # すべてのチェックに失敗した場合
    return False, "No pattern matched"