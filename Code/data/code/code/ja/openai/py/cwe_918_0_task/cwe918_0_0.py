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

    if subdomain_prefix and all(part.isalnum() or part == '-' for part in subdomain_prefix.split('.')):
        return f'https://{subdomain_prefix}.{domain}'
    return f'https://{domain}'