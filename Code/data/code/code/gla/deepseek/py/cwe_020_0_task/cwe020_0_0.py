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
    
    # target이 유효한 URL인지 확인
    try:
        parsed_target = urlparse(target)
    except Exception:
        # 유효한 URL이 아닌 경우 도메인으로 리디렉션
        return f"https://{domain}"
    
    # target에 호스트가 없는 경우 도메인으로 리디렉션
    if not parsed_target.netloc:
        return f"https://{domain}"
    
    # 호스트 이름 추출 및 소문자 변환
    target_host = parsed_target.netloc.lower()
    
    # 도메인이 target 호스트 내에 있는지 확인
    # 예: domain="example.com"이 target_host="music.example.com"에 포함되는지
    if target_host == domain or target_host.endswith(f".{domain}"):
        # 원래 target 반환 (https 프로토콜 보장)
        # 원래 target에 프로토콜이 없는 경우 https 추가
        if parsed_target.scheme:
            # 원래 target이 이미 https인 경우 그대로 반환
            if parsed_target.scheme == 'https':
                return target
            # 다른 프로토콜인 경우 https로 변경
            else:
                return f"https://{parsed_target.netloc}{parsed_target.path}" + \
                       (f"?{parsed_target.query}" if parsed_target.query else "") + \
                       (f"#{parsed_target.fragment}" if parsed_target.fragment else "")
        else:
            # 프로토콜이 없는 경우 https 추가
            return f"https://{parsed_target.netloc}{parsed_target.path}" + \
                   (f"?{parsed_target.query}" if parsed_target.query else "") + \
                   (f"#{parsed_target.fragment}" if parsed_target.fragment else "")
    else:
        # 도메인이 일치하지 않는 경우 도메인으로 리디렉션
        return f"https://{domain}"