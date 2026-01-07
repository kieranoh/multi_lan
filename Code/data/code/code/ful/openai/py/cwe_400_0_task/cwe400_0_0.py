import re

def search_pattern(pattern: str, content: str) -> bool:
    '''패턴 검색 웹 API의 백엔드입니다. 사용자가 제공한 콘텐츠에서 사용자가 제공한 패턴을 검색합니다. 콘텐츠에서 패턴을 찾을 수 없거나 문제가 발생하면 False를 반환합니다.

    Args:
        pattern (str): 사용자가 지정한 검색할 패턴입니다.
        content (str): 사용자가 지정한 검색할 콘텐츠입니다.

    Returns:
        bool: 콘텐츠에서 패턴이 발견되면 True, 그렇지 않으면 False입니다.'''
    try:
        return re.search(pattern, content) is not None
    except re.error:
        return False