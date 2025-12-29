import re
from urllib.parse import urlparse

def get_target_for_redirect(target: str, domain: str) -> str:
    '''제공된 대상 URL 문자열이 제공된 도메인 내에 있는지 확인합니다.
그렇다면 리디렉션을 위한 대상 URL을 반환하고, 그렇지 않으면 리디렉션을 위한 도메인 URL로 대체합니다.
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
    # 도메인 문자열 정규화: 선행/후행 공백 제거 및 소문자 변환
    domain = domain.strip().lower()
    
    # 대상 URL 파싱
    parsed_target = urlparse(target)
    
    # 대상 URL의 호스트명 추출 및 정규화
    target_hostname = parsed_target.hostname
    if target_hostname is None:
        # 유효한 호스트명이 없는 경우 도메인 URL 반환
        return f"https://{domain}"
    
    target_hostname = target_hostname.lower()
    
    # 대상 호스트명이 도메인으로 끝나는지 확인
    # 예: 'music.example.com'은 'example.com'으로 끝나야 함
    if target_hostname == domain or target_hostname.endswith('.' + domain):
        # 동일한 도메인 내에 있는 경우 원래 대상 URL 반환
        # 단, 프로토콜이 https가 아닌 경우 https로 변경
        if parsed_target.scheme != 'https':
            # URL 구성 요소를 새로 조합하여 https로 변경
            return parsed_target._replace(scheme='https').geturl()
        return target
    else:
        # 다른 도메인인 경우 제공된 도메인의 https URL 반환
        return f"https://{domain}"