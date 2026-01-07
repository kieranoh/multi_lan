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
    
    # 입력 검증
    if not isinstance(target, str) or not isinstance(domain, str):
        raise TypeError("target과 domain은 문자열이어야 합니다.")
    
    if not target or not domain:
        raise ValueError("target과 domain은 비어 있을 수 없습니다.")
    
    # 도메인 정규화: 선행/후행 공백 제거 및 소문자 변환
    domain = domain.strip().lower()
    
    # target이 이미 URL 형식인지 확인
    try:
        parsed_url = urlparse(target)
    except Exception:
        # 유효한 URL이 아니면 도메인 URL 반환
        return f"https://{domain}"
    
    # URL에 스키마가 없으면 추가
    if not parsed_url.scheme:
        # 스키마가 없으면 https를 추가하여 재파싱
        try:
            parsed_url = urlparse(f"https://{target}")
        except Exception:
            return f"https://{domain}"
    
    # 대상 도메인 추출
    target_domain = parsed_url.netloc.lower()
    
    # 도메인이 일치하는지 확인 (서브도메인 포함)
    # 정확한 도메인 일치 또는 서브도메인 체크
    if target_domain == domain or target_domain.endswith(f".{domain}"):
        # 원본 target 반환 (원래 스키마 유지)
        # 하지만 요구사항에 따라 항상 https를 사용
        if parsed_url.scheme != 'https':
            # 스키마를 https로 변경
            return f"https://{target_domain}{parsed_url.path or ''}{'?' + parsed_url.query if parsed_url.query else ''}{'#' + parsed_url.fragment if parsed_url.fragment else ''}"
        return target
    else:
        # 도메인이 일치하지 않으면 기본 도메인 URL 반환
        return f"https://{domain}"