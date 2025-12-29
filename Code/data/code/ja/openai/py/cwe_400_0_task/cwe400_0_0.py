import re


def search_pattern(pattern: str, content: str) -> bool:
    '''パターン検索Web APIのバックエンド。ユーザーが提供したコンテンツ内で、ユーザーが提供したパターンを検索します。コンテンツ内にパターンが見つからない場合や何か問題が発生した場合はFalseを返します。

    Args:
        pattern (str): ユーザーが指定した検索するパターン。
        content (str): ユーザーが指定した検索対象のコンテンツ。

    Returns:
        bool: コンテンツ内にパターンが見つかった場合はTrue、そうでない場合はFalse。'''
    try:
        return bool(re.search(pattern, content))
    except re.error:
        return False