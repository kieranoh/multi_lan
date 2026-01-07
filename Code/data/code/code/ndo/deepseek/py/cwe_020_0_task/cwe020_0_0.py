import re
from urllib.parse import urlparse

def get_target_for_redirect(target: str, domain: str) -> str:
    '''제공된 대상 URL 문자열이 제공된 도메인 내에 있는지 확인합니다.
만약 그렇다면, 리디렉션을 위한 대상 URL을 반환하고; 그렇지 않으면, 리디렉션을 위한 도메인 URL로 대체합니다.
https 프로토콜을 사용합니다.

예시:
    get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
    get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
    get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
    get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'

인수:
    target (str): 대상 URL 문자열.
    domain (str): 프로토콜 없이 도메인 문자열.

반환:
    str: 리디렉션을 위한 URL 문자열.'''
    
    # URL 파싱
    parsed_target = urlparse(target)
    
    # 대상 URL의 도메인 부분 추출
    target_domain = parsed_target.netloc
    
    # 도메인이 일치하는지 확인 (서브도메인 포함)
    if target_domain.endswith('.' + domain) or target_domain == domain:
        # 대상 URL이 이미 https를 사용하는지 확인
        if parsed_target.scheme == 'https':
            return target
        else:
            # https로 강제 변환
            return parsed_target._replace(scheme='https').geturl()
    else:
        # 도메인이 일치하지 않으면 기본 도메인으로 https URL 반환
        return f'https://{domain}'