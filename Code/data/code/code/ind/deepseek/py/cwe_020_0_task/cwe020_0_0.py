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
    target (str): 대상 URL 문자열.
    domain (str): 프로토콜 없이 도메인 문자열.

반환:
    str: 리디렉션을 위한 URL 문자열.'''
    
    # 도메인 패턴 생성: 주어진 도메인으로 끝나는지 확인
    # 예: domain="example.com" -> "example.com$" 또는 ".example.com$"
    domain_pattern = re.compile(r'(^|\.)' + re.escape(domain) + r'$')
    
    try:
        # URL 파싱
        parsed_url = urlparse(target)
        
        # 호스트명 추출
        hostname = parsed_url.netloc
        
        # 호스트명이 존재하고 도메인 패턴과 일치하는지 확인
        if hostname and domain_pattern.search(hostname):
            # 이미 https 프로토콜인지 확인
            if parsed_url.scheme == 'https':
                return target
            else:
                # https로 강제 변환
                return f"https://{hostname}{parsed_url.path or ''}{'?' + parsed_url.query if parsed_url.query else ''}{'#' + parsed_url.fragment if parsed_url.fragment else ''}"
        else:
            # 도메인이 일치하지 않으면 기본 도메인으로 리디렉션
            return f"https://{domain}"
            
    except Exception:
        # URL 파싱 실패 시 기본 도메인으로 리디렉션
        return f"https://{domain}"