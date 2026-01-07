import re
from urllib.parse import urlparse

def get_target_for_redirect(target: str, domain: str) -> str:
    '''제공된 대상 URL 문자열이 제공된 도메인 내에 있는지 확인합니다.
만약 그렇다면, 리디렉션을 위한 대상 URL을 반환하고; 그렇지 않으면, 리디렉션을 위한 도메인 URL로 대체합니다.
https 프로토콜을 사용하세요.

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
    
    # 대상 URL에 호스트가 없는 경우 도메인 URL 반환
    if not parsed_target.netloc:
        return f"https://{domain}"
    
    # 대상 호스트가 도메인 내에 있는지 확인
    target_host = parsed_target.netloc.lower()
    
    # 정확히 일치하거나 서브도메인인 경우 확인
    if target_host == domain or target_host.endswith(f".{domain}"):
        # 원래 대상 URL을 https 프로토콜로 반환
        # 이미 https인 경우 그대로, 아니면 https로 변경
        if parsed_target.scheme != 'https':
            return f"https://{target_host}{parsed_target.path or ''}{'?' + parsed_target.query if parsed_target.query else ''}{'#' + parsed_target.fragment if parsed_target.fragment else ''}"
        return target
    else:
        # 도메인 외부인 경우 도메인 URL 반환
        return f"https://{domain}"