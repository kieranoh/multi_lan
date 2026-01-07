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
    # 도메인 정규화: 선행/후행 공백 제거 및 소문자 변환
    domain = domain.strip().lower()
    
    # 대상 URL 파싱
    parsed_target = urlparse(target)
    
    # 대상 URL의 호스트명 추출 및 정규화
    target_hostname = parsed_target.hostname
    if target_hostname is None:
        # 유효한 호스트명이 없는 경우 도메인 URL 반환
        return f"https://{domain}"
    
    target_hostname = target_hostname.lower()
    
    # 대상 호스트명이 도메인 내에 있는지 확인
    # 1. 정확히 일치하는 경우
    if target_hostname == domain:
        return target
    
    # 2. 서브도메인인 경우 (예: music.example.com은 example.com의 서브도메인)
    # 도메인이 .example.com과 같이 시작하는지 확인하여 example.com의 서브도메인인지 검사
    if target_hostname.endswith('.' + domain):
        return target
    
    # 3. 그 외의 경우 도메인 URL 반환
    return f"https://{domain}"