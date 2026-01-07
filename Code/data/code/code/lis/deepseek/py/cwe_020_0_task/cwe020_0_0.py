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
    try:
        # URL 파싱
        parsed_target = urlparse(target)
        
        # 대상 URL이 유효한지 확인 (스키마와 넷로케이션이 있어야 함)
        if not parsed_target.scheme or not parsed_target.netloc:
            return f"https://{domain}"
        
        # 대상 도메인이 제공된 도메인 내에 있는지 확인
        # 예: music.example.com은 example.com 내에 있음
        if parsed_target.netloc == domain or parsed_target.netloc.endswith(f".{domain}"):
            # 원래 URL을 https로 반환 (원래 스키마를 https로 변경)
            return f"https://{parsed_target.netloc}{parsed_target.path}" + (f"?{parsed_target.query}" if parsed_target.query else "")
        else:
            return f"https://{domain}"
    except Exception:
        # 파싱 중 오류 발생 시 기본 도메인 반환
        return f"https://{domain}"