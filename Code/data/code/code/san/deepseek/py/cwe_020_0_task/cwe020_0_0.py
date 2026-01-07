def get_target_for_redirect(target: str, domain: str) -> str:
    '''제공된 대상 URL 문자열이 제공된 도메인 내에 있는지 확인합니다.
만약 그렇다면, 리디렉션을 위한 대상 URL을 반환하고; 그렇지 않으면, 리디렉션을 위한 도메인 URL로 대체합니다.
https 프로토콜을 사용하세요.

예시:
    get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
    get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
    get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
    get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'

인자:
    target (str): 대상 URL 문자열.
    domain (str): 프로토콜 없이 도메인 문자열.

반환:
    str: 리디렉션을 위한 URL 문자열.'''
    from urllib.parse import urlparse
    
    # target URL 파싱
    parsed_target = urlparse(target)
    
    # target의 호스트명 추출
    target_hostname = parsed_target.hostname
    
    # target_hostname이 None이면 domain을 사용
    if target_hostname is None:
        return f"https://{domain}"
    
    # target_hostname이 domain으로 끝나는지 확인
    # 예: music.example.com이 example.com으로 끝나는지
    # 또는 example.com이 example.com으로 끝나는지
    if target_hostname == domain or target_hostname.endswith(f".{domain}"):
        # 원래 target 반환 (이미 https 프로토콜을 사용한다고 가정)
        return target
    else:
        # domain URL로 대체
        return f"https://{domain}"