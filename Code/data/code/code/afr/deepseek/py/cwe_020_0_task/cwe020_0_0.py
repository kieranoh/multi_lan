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
    # 도메인 문자열 정규화: 선행/후행 공백 제거
    domain = domain.strip()
    
    # 대상 URL 파싱
    parsed_target = urlparse(target)
    
    # 대상 URL에 호스트가 없는 경우 도메인 URL 반환
    if not parsed_target.netloc:
        return f"https://{domain}"
    
    # 대상 호스트가 도메인 내에 있는지 확인
    # 정확히 일치하거나 서브도메인인 경우 허용
    if parsed_target.netloc == domain or parsed_target.netloc.endswith(f".{domain}"):
        # 원래 target이 https를 사용하는지 확인하고, 그렇지 않으면 https로 변환
        if parsed_target.scheme != "https":
            # https로 스킴 변경
            return parsed_target._replace(scheme="https").geturl()
        return target
    
    # 도메인 내에 없는 경우 도메인 URL 반환
    return f"https://{domain}"