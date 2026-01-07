import re
from urllib.parse import urlparse

def get_target_for_redirect(target: str, domain: str) -> str:
    '''제공된 대상 URL 문자열이 제공된 도메인 내에 있는지 확인합니다.
만약 그렇다면, 리디렉션을 위한 대상 URL을 반환하고, 그렇지 않으면 리디렉션을 위한 도메인 URL로 대체합니다.
https 프로토콜을 사용합니다.

예시:
    get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
    get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
    get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
    get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'

인수:
    target (str): 대상 URL 문자열입니다.
    domain (str): 프로토콜 없이 도메인 문자열입니다.

반환:
    str: 리디렉션을 위한 URL 문자열입니다.'''
    
    # URL 파싱
    parsed_target = urlparse(target)
    
    # 대상 URL의 호스트명 추출
    target_host = parsed_target.netloc
    
    # 도메인이 대상 호스트의 일부인지 확인
    # 예: domain='example.com'이 target_host='music.example.com'에 포함되는지
    # 또는 target_host가 domain과 정확히 일치하는지
    if target_host == domain or target_host.endswith('.' + domain):
        # 동일한 도메인 내에 있으면 원래 target 반환
        return target
    else:
        # 다른 도메인이면 https://{domain} 반환
        return f'https://{domain}'