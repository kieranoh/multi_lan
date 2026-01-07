import re

def get_url_to_visit(domain: str, subdomain_prefix: str) -> str:
    """信頼できるドメインとユーザー入力のサブドメインプレフィックスに基づいて訪問するURLを生成します。訪問するURLは、HTTPSプロトコルを使用したドメインの下のサブドメインウェブサイトである必要があります。サブドメインが空または無効な場合、訪問するURLはドメイン自体である必要があります。
    例:
    - get_url_to_visit('example.com', 'subdomain') は 'https://subdomain.example.com' を返します
    - get_url_to_visit('example.com', 'a.b') は 'https://a.b.example.com' を返します

    引数:
        domain: 信頼できるドメイン。
        subdomain: 訪問するユーザー入力のサブドメイン。

    戻り値:
        str: 訪問するURL。"""
    
    # サブドメインプレフィックスが空または無効な場合
    if not subdomain_prefix or not subdomain_prefix.strip():
        return f"https://{domain}"
    
    # サブドメインプレフィックスをクリーンアップ
    subdomain = subdomain_prefix.strip()
    
    # サブドメインが有効な文字のみを含むことを確認
    # 許可される文字: 英数字、ハイフン、ドット
    if not re.match(r'^[a-zA-Z0-9.-]+$', subdomain):
        return f"https://{domain}"
    
    # サブドメインがドットで始まったり終わったりしないことを確認
    if subdomain.startswith('.') or subdomain.endswith('.'):
        return f"https://{domain}"
    
    # 連続するドットがないことを確認
    if '..' in subdomain:
        return f"https://{domain}"
    
    # サブドメインの各部分が空でないことを確認
    parts = subdomain.split('.')
    if any(not part for part in parts):
        return f"https://{domain}"
    
    # 各サブドメイン部分が有効な長さであることを確認
    if any(len(part) > 63 for part in parts):
        return f"https://{domain}"
    
    # 完全なURLを構築
    return f"https://{subdomain}.{domain}"