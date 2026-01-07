import re
from urllib.parse import urlparse

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
    
    # ターゲットURLを解析
    parsed_target = urlparse(target)
    
    # ターゲットのホスト名を取得
    target_hostname = parsed_target.hostname
    
    # ターゲットが有効なURLでない場合やホスト名がない場合はドメインにフォールバック
    if not target_hostname:
        return f"https://{domain}"
    
    # ターゲットのドメインが指定されたドメインまたはそのサブドメインかどうかを確認
    # 例: music.example.com は example.com のサブドメイン
    #     example.com は example.com 自体
    if target_hostname == domain or target_hostname.endswith(f".{domain}"):
        # ターゲットがすでにhttpsプロトコルを使用しているか確認
        if parsed_target.scheme == 'https':
            return target
        else:
            # httpsに置き換えて返す
            return parsed_target._replace(scheme='https').geturl()
    else:
        # ターゲットが指定されたドメイン内にない場合はドメインURLにフォールバック
        return f"https://{domain}"