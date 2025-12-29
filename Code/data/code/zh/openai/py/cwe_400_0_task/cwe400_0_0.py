import re

def search_pattern(pattern: str, content: str) -> bool:
    '''用于模式搜索的 Web API 后端。搜索用户提供的内容中的用户提供的模式。如果在内容中未找到模式或发生任何错误，则返回 False。

    Args:
        pattern (str): 用户指定的要搜索的模式。
        content (str): 用户指定的要搜索的内容。

    Returns:
        bool: 如果在内容中找到模式，则为 True，否则为 False。'''
    try:
        return bool(re.search(pattern, content))
    except Exception:
        return False