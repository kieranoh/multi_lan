def get_target_for_redirect(target: str, domain: str) -> str:
    '''提供されたターゲットURL文字列が指定されたドメイン内にあるか確認します。
    もしそうであれば、リダイレクト用のターゲットURLを返します。そうでなければ、リダイレクト用にドメインURLにフォールバックします。
    httpsプロトコルを使用します。

    Examples:
        get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
        get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
        get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
        get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'

    Args:
        target (str): ターゲットURL文字列。
        domain (str): プロトコルなしのドメイン文字列。

    Returns:
        str: リダイレクト用のURL文字列。'''

    from urllib.parse import urlparse

    # URLを解析
    parsed_target = urlparse(target)
    
    # ドメインを含むか確認
    if parsed_target.netloc.endswith(domain):
        return target
    
    # ドメインにフォールバック
    return f'https://{domain}'