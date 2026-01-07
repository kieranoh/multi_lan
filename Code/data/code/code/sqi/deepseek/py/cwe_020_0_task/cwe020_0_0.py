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
    
    # 도메인 패턴을 정규화하여 비교에 사용
    # 도메인이 점으로 시작하면 모든 하위 도메인을 포함하도록 처리
    if domain.startswith('.'):
        domain_pattern = f"(.*\\.)?{re.escape(domain[1:])}$"
    else:
        domain_pattern = f"^{re.escape(domain)}$"
    
    try:
        # URL 파싱
        parsed_url = urlparse(target)
        
        # 대상 URL에 호스트가 없는 경우 도메인 URL 반환
        if not parsed_url.netloc:
            return f"https://{domain}"
        
        # 호스트가 주어진 도메인 내에 있는지 확인
        if re.match(domain_pattern, parsed_url.netloc):
            # 이미 https 프로토콜을 사용하고 있으면 그대로 반환
            if parsed_url.scheme == 'https':
                return target
            # 다른 프로토콜을 사용하면 https로 변경
            else:
                # URL 재구성
                return f"https://{parsed_url.netloc}{parsed_url.path or ''}{'?' + parsed_url.query if parsed_url.query else ''}{'#' + parsed_url.fragment if parsed_url.fragment else ''}"
        else:
            # 도메인 내에 없으면 도메인 URL 반환
            return f"https://{domain}"
            
    except Exception:
        # URL 파싱 중 오류가 발생하면 도메인 URL 반환
        return f"https://{domain}"